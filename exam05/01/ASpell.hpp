#ifndef ASPELL_HPP
# define ASPELL_HPP

# include "ATarget.hpp"

class ATarget;

class ASpell
{
	protected:
		std::string _name;
		std::string _effects;

	public:
		ASpell(const std::string& name, const std::string& effects)
		{
			_name = name;
			_effects = effects;
		}

		virtual ~ASpell() {}
		ASpell(const ASpell& spell) {*this = spell;}
		ASpell& operator= (const ASpell& spell) 
		{
			_name = spell._name;
			_effects = spell._effects;
			return *this;
		}

		const std::string& getName() const {return _name;}
		const std::string& getEffects() const {return _effects;}

		virtual ASpell* clone() const = 0;
		void launch(const ATarget& target) const;
};

#endif
