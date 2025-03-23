#ifndef PU_VELOCIDAD_H
#define PU_VELOCIDAD_H
#include "powerup.h"
#include "esc_partida.h"

class pu_velocidad : public powerup {

public:
	pu_velocidad(Vector2u tam_resol);
	void aplicar(prota &p, esc_partida &ep) override;

};

#endif

