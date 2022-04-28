#ifndef ATARGET_HPP
# define ATARGET_HPP

# include <iostream>
# include "ASpell.hpp"

class ASpell;

class ATarget
{
	protected:
		std::string _type;

	public:
		ATarget(const std::string& type) {_type = type;}
		virtual ~ATarget() {}
		ATarget(const ATarget& target) {*this = target;}
		ATarget& operator= (const ATarget& target)
		{
			_type = target._type;
			return *this;
		}

		const std::string& getType() const {return _type;}

		virtual ATarget* clone() const = 0;
		void getHitBySpell(const ASpell& spell) const;
};

#endif
