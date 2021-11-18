#ifndef ABSTRACT_FRONTEND_H
#define ABSTRACT_FRONTEND_H

class Game;

class AbstractFrontend
{
public:
	virtual void run(Game * game) = 0;
	virtual ~AbstractFrontend () = default;
private:

};

#endif //ABSTRACT_FRONTEND_H