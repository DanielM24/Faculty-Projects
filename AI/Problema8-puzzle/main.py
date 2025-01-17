"""Problema 8-puzzle"""

import copy


def extrage_pozitii(tabla):
	return {
		tablita: (i, j)
		for i, rand in enumerate(tabla)
		for j, tablita in enumerate(rand)
	}


configuratie_initiala = [[4, 3, 2], [8, 7, 5], [1, 0, 6]]
configuratie_finala = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]

pozitii_finale = extrage_pozitii(configuratie_finala)


""" definirea problemei """


class Problema:
	def __init__(self):
		self.noduri = [
			Nod(configuratie_initiala),
			Nod(configuratie_finala),
		]
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

	def adauga_nod(self, info):
		nod_nou = Nod(info)
		self.noduri.append(nod_nou)
		return nod_nou


class Nod:
	def __init__(self, tablite):
		self.info = tablite
		self.h = 0

		pozitii = extrage_pozitii(tablite)

		for tablita in range(9):
			a = pozitii[tablita]
			b = pozitii_finale[tablita]
			if a != b:
				self.h += abs(a[0] - b[0]) + abs(a[1] - b[1])

	def __str__(self):
		return "({}, h={})".format(self.info, self.h)

	def __repr__(self):
		return f"({self.info}, h={self.h})"


class Arc:
	def __init__(self, capat, varf, cost):
		self.capat = capat
		self.varf = varf
		self.cost = cost


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
		succesori = []

		tabla = self.nod_graf.info
		pozitii = extrage_pozitii(tabla)
		poz_libera = pozitii[0]
		rand, col = poz_libera

		if rand > 0:
			copie = copy.deepcopy(tabla)
			copie[rand][col] = copie[rand - 1][col]
			copie[rand - 1][col] = 0

			nod_nou = NodParcurgere.problema.adauga_nod(copie)
			succesori.append((nod_nou, 1))

		if col > 0:
			copie = copy.deepcopy(tabla)
			copie[rand][col] = copie[rand][col - 1]
			copie[rand][col - 1] = 0

			nod_nou = NodParcurgere.problema.adauga_nod(copie)
			succesori.append((nod_nou, 1))

		if rand < 2:
			copie = copy.deepcopy(tabla)
			copie[rand][col] = copie[rand + 1][col]
			copie[rand + 1][col] = 0

			nod_nou = NodParcurgere.problema.adauga_nod(copie)
			succesori.append((nod_nou, 1))

		if col < 2:
			copie = copy.deepcopy(tabla)
			copie[rand][col] = copie[rand][col + 1]
			copie[rand][col + 1] = 0

			nod_nou = NodParcurgere.problema.adauga_nod(copie)
			succesori.append((nod_nou, 1))

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
	sir += "]"
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

	print("Numar de mutari:", nod_curent.g)

	if len(lopen) == 0:
		print("Lista open e vida, nu avem drum de la nodul start la nodul scop")
	else:
		print("Drum de cost minim: " + str_info_noduri(nod_curent.drum_arbore()))


if __name__ == "__main__":
	problema = Problema()
	NodParcurgere.problema = problema
	a_star()
