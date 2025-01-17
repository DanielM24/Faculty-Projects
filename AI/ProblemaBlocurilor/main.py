""" Problema blocurilor din laboratorul 4 """


def extrage_pozitii(stive):
	# dictionar în care rețin că litera X se află pe stiva i poziția j
	pozitii = {}
	for i, stiva in enumerate(stive):
		for j, cub in enumerate(stiva):
			pozitii[cub] = (i, j)
	return pozitii


# datele de intrare

# numărul de stive
N = 3

# etichetele cuburilor
cuburi = ['a', 'b', 'c', 'd']

# numărul de cuburi
M = len(cuburi)

# configurația inițială a cuburilor
configuratie_initiala = [['a'], ['b', 'c'], ['d']]

# configurația țintă
configuratie_finala = [['b', 'c'], [], ['d', 'a']]

pozitii_finale = extrage_pozitii(configuratie_finala)

""" Definirea Problemei """


class Nod:
	def __init__(self, stive):
		self.info = stive

		# calculez euristica pentru acest nod
		self.h = 0

		distanta = 0

		# văd pe ce poziții se află cuburile din această configurație
		pozitii = extrage_pozitii(stive)

		# trec prin toate cuburile
		for cub in cuburi:
			if pozitii[cub] != pozitii_finale[cub]:
				distanta += 1

	def __str__(self):
		return "({}, h={})".format(self.info, self.h)

	def __repr__(self):
		return f"({self.info}, h={self.h})"


class Arc:
	def __init__(self, capat, varf):
		self.capat = capat
		self.varf = varf
		self.cost = 1  # toate mutările au cost 1


class Problema:
	def __init__(self):
		self.noduri = [
			Nod(configuratie_initiala)
		]
		self.arce = []
		self.nod_start = self.noduri[0]
		self.nod_scop = configuratie_finala

	def cauta_nod_nume(self, info):
		"""Stiind doar informatia "info" a unui nod,
		trebuie sa returnati fie obiectul de tip Nod care are acea informatie,
		fie None, daca nu exista niciun nod cu acea informatie."""
		for nod in self.noduri:
			if nod.info == info:
				return nod
		# la capătul funcției dă return None implicit


""" Sfarsit definire problema """

""" Clase folosite in algoritmul A* """


class NodParcurgere:
	"""O clasa care cuprinde informatiile asociate unui nod din listele open/closed
		Cuprinde o referinta catre nodul in sine (din graf)
		dar are ca proprietati si valorile specifice algoritmului A* (f si g).
		Se presupune ca h este proprietate a nodului din graf

	"""

	problema = None		# atribut al clasei

	def __init__(self, nod_graf, parinte=None, g=0, f=None):
		self.nod_graf = nod_graf	 # obiect de tip Nod
		self.parinte = parinte		 # obiect de tip Nod
		self.g = g					 # costul drumului de la radacina pana la nodul curent
		if f is None:
			self.f = self.g + self.nod_graf.h
		else:
			self.f = f

	def drum_arbore(self):
		"""
			Functie care calculeaza drumul asociat unui nod din arborele de cautare.
			Functia merge din parinte in parinte pana ajunge la radacina
		"""
		nod_c = self
		drum = [nod_c]
		while nod_c.parinte is not None:
			drum = [nod_c.parinte] + drum
			nod_c = nod_c.parinte
		return drum

	def contine_in_drum(self, nod):
		"""
			Functie care verifica daca nodul "nod" se afla in drumul dintre radacina si nodul curent (self).
			Verificarea se face mergand din parinte in parinte pana la radacina
			Se compara doar informatiile nodurilor (proprietatea info)
			Returnati True sau False.

			"nod" este obiect de tip Nod (are atributul "nod.info")
			"self" este obiect de tip NodParcurgere (are "self.nod_graf.info")
		"""
		nod_curent = self
		while nod_curent:
			if nod_curent.nod_graf.info == nod.info:
				return True
			nod_curent = nod_curent.parinte
		return False

	# se modifica in functie de problema
	def expandeaza(self):
		"""Pentru nodul curent (self) parinte, trebuie sa gasiti toti succesorii (fiii)
		si sa returnati o lista de tupluri (nod_fiu, cost_muchie_tata_fiu),
		sau lista vida, daca nu exista niciunul.
		(Fiecare tuplu contine un obiect de tip Nod si un numar.)
		"""
		stive = self.nod_graf.info
		succesori = []
		# pot obține o nouă poziție mutând un cub de pe o stivă nevidă pe o altă stivă
		for stiva_sursa in range(N):
			for stiva_destinatie in range(N):
				if stiva_sursa == stiva_destinatie:
					continue  # ignor mutarea unui cub pe aceeași stivă

				if not stive[stiva_sursa]:
					continue  # nu pot să mut de pe o stivă vidă

				# rețin ultimul bloc
				cub_de_mutat = stive[stiva_sursa][-1]

				stive_noi = []
				for i in range(N):
					if i == stiva_sursa:
						# nu copiez și cubul din vârf
						stiva_noua = stive[i][:-1]
					elif i == stiva_destinatie:
						# adaug cubul mutat
						stiva_noua = stive[i] + [cub_de_mutat]
					else:
						stiva_noua = stive[i]

					stive_noi.append(stiva_noua)

				# văd dacă nu cumva am explorat deja această configurație
				succesor = problema.cauta_nod_nume(stive_noi)

				if not succesor:
					nod_nou = Nod(stive_noi)
					problema.noduri.append(nod_nou)
					succesor = nod_nou

				cost = 1  # orice mutare are cost 1
				succesori.append((succesor, cost))

		return succesori

	# se modifica in functie de problema

	def test_scop(self):
		return self.nod_graf.info == self.problema.nod_scop

	def __str__(self):
		parinte = self.parinte if self.parinte is None else self.parinte.nod_graf.info
		return f"({self.nod_graf}, parinte={parinte}, f={self.f}, g={self.g})"


""" Algoritmul A* """


def str_info_noduri(l):
	"""
		o functie folosita strict in afisari - poate fi modificata in functie de problema
	"""
	sir = "["
	for x in l:
		sir += str(x)+"  "
	sir += "] \n"
	return sir


def afis_succesori_cost(l):
	"""
		o functie folosita strict in afisari - poate fi modificata in functie de problema
	"""
	sir = ""
	for (x, cost) in l:
		sir += "\nnod: "+str(x)+", cost arc:" + str(cost)

	return sir


def in_lista(l, nod):
	"""
	lista "l" contine obiecte de tip NodParcurgere
	"nod" este de tip Nod
	"""
	for i in range(len(l)):
		if l[i].nod_graf.info == nod.info:
			return l[i]
	return None


def a_star():
	rad_arbore = NodParcurgere(NodParcurgere.problema.nod_start)
	lopen = [rad_arbore]		# open va contine elemente de tip NodParcurgere
	closed = []				# closed va contine elemente de tip NodParcurgere

	while lopen:  # cât timp mai avem noduri neexplorate
		# se scoate nodul din open
		nod_curent = lopen.pop(0)

		# se pune în closed
		closed.append(nod_curent)

		if nod_curent.test_scop():  # am ajuns la țintă
			break

		drum = nod_curent.drum_arbore()

		for succesor, cost in nod_curent.expandeaza():
			if in_lista(drum, succesor):
				continue

			nod_open = in_lista(lopen, succesor)  # îl caut în lista open
			nod_closed = in_lista(closed, succesor)  # îl caut în lista closed

			# calculez distanța dacă ar fi să trec prin `nod_curent` să ajung la succesor
			g_nou = nod_curent.g + cost

			if nod_open:  # dacă l-am găsit încerc să îl actualizez
				# dacă am găsit o distanță mai bună
				if g_nou < nod_open.g:
					nod_open.g = g_nou
					nod_open.f = g_nou + nod_open.nod_graf.h
					nod_open.parinte = nod_curent

			elif nod_closed:
				f_nou = g_nou + nod_closed.nod_graf.h

				if f_nou < nod_closed.f:
					nod_closed.g = g_nou
					nod_closed.f = f_nou + nod_closed.nod_graf.h
					nod_closed.parinte = nod_curent

					# dacă l-am actualizat, se mută înapoi în open,
					# ca să îi re-explorez vecini
					lopen.append(nod_closed)
			else:
				# nu e în nicio listă, îl pun în open inițial
				nod_nou = NodParcurgere(
					nod_graf=succesor,
					parinte=nod_curent,
					g=g_nou
				)

				lopen.append(nod_nou)

		# teoretic ar trebui ca `open` să fie max heap,
		# dar merge și dacă îl sortez și scot mereu minimul
		lopen.sort(key=lambda nod: nod.f)

	print("\n------------------ Concluzie -----------------------")

	if len(lopen) == 0:
		print("Lista open e vida, nu avem drum de la nodul start la nodul scop")
	else:
		print("Drum de cost minim: " + str_info_noduri(nod_curent.drum_arbore()))


if __name__ == "__main__":
	problema = Problema()
	NodParcurgere.problema = problema
	a_star()
