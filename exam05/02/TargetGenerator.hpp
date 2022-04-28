#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

# include <iostream>
# include <vector>
# include "ATarget.hpp"

class TargetGenerator
{
	private:
		std::vector<ATarget*> _book;

		TargetGenerator(const TargetGenerator*);
		TargetGenerator& operator= (const TargetGenerator&);

	public:
		TargetGenerator() {}
		~TargetGenerator()
		{
			std::vector<ATarget*>::iterator it = _book.begin();
			for ( ; it != _book.end(); )
			{
				delete *it;
				it = _book.erase(it);
			}
		}

		void learnTargetType(ATarget* target)
		{
			std::vector<ATarget*>::iterator it = _book.begin();
			for ( ; it != _book.end(); it++)
				if ((*it)->getType() == target->getType())
					return ;
			_book.push_back(target->clone());
		}

		void forgetTargetType(const std::string& target_type)
		{
			std::vector<ATarget*>::iterator it = _book.begin();
			for ( ;it != _book.end(); it++)
			{
				if ((*it)->getType() == target_type)
				{
					delete *it;
					_book.erase(it);
					return ;
				}
			}
		}

		ATarget* createTarget(const std::string& target_type)
		{
			std::vector<ATarget*>::iterator it = _book.begin();
			for ( ;it != _book.end(); it++)
				if ((*it)->getType() == target_type)
					return *it;
			return NULL;
		}
};

#endif
