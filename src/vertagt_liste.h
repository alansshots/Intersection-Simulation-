#pragma once

#include "vertagt_aktion.h"
#include <list>

namespace vertagt {
	template <class T>
	class VListe {
	private:
		std::list<T> p_objekte;
		std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

	public:
		// Typdefinitionen
		using iterator = typename std::list<T>::iterator;
		using const_iterator = typename std::list<T>::const_iterator;

		// Konstruktoren
		VListe() = default; // Benötigt man einen Standardkonstruktor?
		// Destruktor
		~VListe()
		{
			vAktualisieren();
			p_objekte.clear();
		}

		void clear()
		{
			p_objekte.clear();
			//Entfernt alle Elemente aus dem Kontainer.
		}

		// Lesefunktionen
		const_iterator begin() const
		{
			return p_objekte.begin();
		}
		const_iterator end() const
		{
			return p_objekte.end();
		}
		iterator begin()
		{
			return p_objekte.begin();
		}
		iterator end()
		{
			return p_objekte.end();
		}
		bool empty() const
		{
			return p_objekte.empty(); //ob der Liste leer ist
		}

		// Schreibfunktionen
		void push_back(T obj)
		{
			p_aktionen.push_back(make_unique<VPushBack<T>>(p_objekte, move(obj)));
		}

		void push_front(T obj)
		{
			p_aktionen.push_front(make_unique<VPushFront<T>>(p_objekte, move(obj)));
		}

		void erase(iterator it)
		{
			p_aktionen.push_back(make_unique<VErase<T>>(p_objekte, it));
			//Nicht erase, weil wir wollen ein Element ERZEUGEN (create), das loeschen erfolgt dann bei vAktualisieren()
		}

		// Änderungen auf Objektliste übertragen
		void vAktualisieren()
		{
			// Änderungen auf Objektliste übertragen
			for (auto& pАktion : p_aktionen)
			{
				// Aktion ausführen
				// Aktionszeiger auf 1. Element bestimmen
				unique_ptr <VAktion<T>> p_аktion = move(p_aktionen.front());
//				p_aktionen.front() = erstes element in p_aktionen: (VPushFront, VPushBack oder VErase)

				// Aktion ausführen
				p_аktion->vAusfuehren(); //pushback, pushfront oder erase wird ausgefuehrt.
				p_aktionen.pop_front(); //element wird geloescht -> naechste Element erste wird.
				p_аktion.reset();
			}

			// Aktionsliste löschen
			p_aktionen.clear();

		}
	};
} // namespace vertagt
