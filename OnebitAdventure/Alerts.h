// Alerts.h
// ------------------------------------------------------------------------------

#pragma once
#ifndef ALERTS_H
#define ALERTS_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Object.h"
#include "TileSet.h"
#include "Animation.h"

// ------------------------------------------------------------------------------

class Alerts
{
protected:
    // --------------------------------------------------------------------------------------------
    // Atributos de Sprites e Animação e etc

    Sprite * spriteAlerts;                                       // Sprite dos alertas
    Color * color;                                               // Cor do alerta
    static Color defaultColor;                                   // Cor padrão vermelha

    // --------------------------------------------------------------------------------------------
    // Métodos Auxiliares

    bool nextFrame;                                              // Próximo frame
    float x, y, scala;                                           // Posição do alerta

public:
    bool draw;                                                   // Desenha o alerta

    Alerts(float x, float y, float scala);                       // Construtor
    ~Alerts();                                                   // Destrutor

    // --------------------------------------------------------------------------------------------

	float GetX() const;                                          // Retorna a posição x
	float GetY() const;                                          // Retorna a posição y
    void UpdateAnimation(Color* color = nullptr);                // Atualiza a animação
    void Draw();                                                 // Desenha o ataque
};

// ------------------------------------------------------------------------------

inline float Alerts::GetX() const
{
	return x;
}

inline float Alerts::GetY() const
{
	return y;
}

inline void Alerts::Draw()
{
	spriteAlerts->Draw(x ,y , Layer::MIDDLE, scala, 0.0f, *color);
}

#endif
// ------------------------------------------------------------------------------