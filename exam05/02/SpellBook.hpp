#ifndef SPELLBOOK_HPP
# define SPELLBOOK_HPP

# include <iostream>
# include <vector>
# include "ASpell.hpp"

class SpellBook
{
	private:
		std::vector<ASpell*> _book;

		SpellBook(const SpellBook&);
		SpellBook& operator= (const SpellBook&);

	public:
		SpellBook() {}
		~SpellBook()
		{
			std::vector<ASpell*>::iterator it = _book.begin();
			for ( ; it != _book.end(); )
			{
				delete *it;
				it = _book.erase(it);
			}
		}

		void learnSpell(ASpell* spell)
		{
			std::vector<ASpell*>::iterator it = _book.begin();
			for ( ; it != _book.end(); it++)
				if ((*it)->getName() == spell->getName())
					return ;
			_book.push_back(spell->clone());
		}

		void forgetSpell(const std::string& spell_name)
		{
			std::vector<ASpell*>::iterator it = _book.begin();
			for ( ; it != _book.end(); it++)
			{
				if ((*it)->getName() == spell_name)
				{
					delete *it;
					_book.erase(it);
					return ;
				}
			}
		}

		ASpell* createSpell(const std::string& spell_name)
		{
			std::vector<ASpell*>::iterator it = _book.begin();
			for ( ; it != _book.end(); it++)
				if ((*it)->getName() == spell_name)
					return *it;
			return NULL;
		}
};

#endif
