#pragma once


struct Planet
{
	double radius, mass;
	Vector position, velocity, acceleration, Momentum;
	int		iNr;
	double	dL2Dist;  
	int		iHot = 0;
	
	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;
	SDL_Texture* texture2;

	Planet(double mass, Vector position, Vector velocity, int iNr = 0, double dL2Dist = 0 );

//	double updateAccs(std::vector<Planet*>& others, int iPNr);
//	void updateVelocityInit(std::vector<Planet*>& Planets);
	void updateVelocityAndPosition();
	void updatePosition();
	void updateAccs( int iPlanet, std::vector<Planet*> planets);
	
	void render();
};

double updateAccs( int i, std::vector<Planet*>& planets);
