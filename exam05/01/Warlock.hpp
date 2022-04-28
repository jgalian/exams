#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <vector>
# include "ASpell.hpp"
# include "ATarget.hpp"

class Warlock
{
	private:
		std::string _name;
		std::string _title;
		std::vector<ASpell*> _book;

		Warlock();
		Warlock(const Warlock&);
		Warlock& operator= (const Warlock&);

	public:
		Warlock(const std::string& name, const std::string& title)
		{
			_name = name;
			_title = title;
			std::cout << _name << ": This looks like another boring day." << std::endl;
		}

		~Warlock() 
		{
			std::vector<ASpell*>::iterator it = _book.begin();
			for ( ; it != _book.end() ; )
			{
				delete *it;
				it = _book.erase(it);
			}
			std::cout << _name << ": My job here is done!" << std::endl;
		}

		const std::string& getName() const {return _name;}
		const std::string& getTitle() const {return _title;}
		void setTitle(const std::string& title) {_title = title;}

		void introduce() const {std::cout << _name << ": I am " << _name << ", " << _title << "!" << std::endl;}
		void learnSpell(ASpell* spell) 
		{
			std::vector<ASpell*>::iterator it = _book.begin();
			for ( ; it != _book.end() ; it++)
				if ((*it)->getName() == spell->getName())
					return ;
			_book.push_back(spell->clone());
		}

		void forgetSpell(const std::string& spell_name)
		{
			std::vector<ASpell*>::iterator it = _book.begin();
			for ( ; it != _book.end() ; it++)
			{
				if ((*it)->getName() == spell_name)
				{
					delete *it;
					_book.erase(it);
					return ;
				}
			}
		}

		void launchSpell(const std::string& spell_name, const ATarget& target)
		{
			std::vector<ASpell*>::iterator it = _book.begin();
			for ( ; it != _book.end() ; it++)
				if ((*it)->getName() == spell_name)
					(*it)->launch(target);
		}
};

#endif
