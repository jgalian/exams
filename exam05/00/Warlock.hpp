#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>

class Warlock
{
	private:
		std::string _name;
		std::string _title;

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

		~Warlock() {std::cout << _name << ": My job here is done!" << std::endl;}

		const std::string& getName() const {return _name;}
		const std::string& getTitle() const {return _title;}
		void setTitle(const std::string& title) {_title = title;}

		void introduce() const {std::cout << _name << ": I am " << _name << ", " << _title << "!" << std::endl;}
};

#endif
