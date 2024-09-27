/**********************************************************************************
// Sprite (C�digo Fonte)
//
// Cria��o:     11 Jul 2007
// Atualiza��o: 23 Ago 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para representar um sprite
//
**********************************************************************************/

#include "Sprite.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos das classes

// valores de profundidade predefinidos
const float Layer::FRONT = 0.01f;
const float Layer::UPPER = 0.25f;
const float Layer::MIDDLE = 0.50f;
const float Layer::LOWER = 0.75f;
const float Layer::BACK = 0.99f;

// ---------------------------------------------------------------------------------

Sprite::Sprite(string filename)
{
    // carrega imagem
    image = new Image(filename);
    localImage = true;

    // configura sprite
    sprite.width = image->Width();
    sprite.height = image->Height();
    sprite.texture = image->View();
}

// ---------------------------------------------------------------------------------

Sprite::Sprite(string filename, uint width, uint height)
{
    // carrega imagem
    image = new Image(filename, width, height);
    localImage = true;

    // configura sprite
    sprite.width = image->Width();
    sprite.height = image->Height();
    sprite.texture = image->View();
}

// ---------------------------------------------------------------------------------

Sprite::Sprite(const Image* img)
{
    // aponta para imagem externa
    image = img;
    localImage = false;

    // configura sprite
    sprite.width = image->Width();
    sprite.height = image->Height();
    sprite.texture = image->View();
}

// ---------------------------------------------------------------------------------

Sprite::~Sprite()
{
    if (localImage)
        delete image;
}

// ---------------------------------------------------------------------------------

void Sprite::Draw(float x, float y, float z, float scale, float rotation, Color color)
{
    sprite.x = x;
    sprite.y = y;
    sprite.depth = z;
    sprite.scale = scale;
    sprite.rotation = rotation;
    sprite.color = color;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(sprite);
}

// ---------------------------------------------------------------------------------

void Sprite::DrawResize(float x, float y, float width, float height, float z, float scale, float rotation, Color color)
{
    sprite.width = width;
    sprite.height = height;
    sprite.x = x;
    sprite.y = y;
    sprite.depth = z;
    sprite.scale = scale;
    sprite.rotation = rotation;
    sprite.color = color;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(sprite);
}

// ---------------------------------------------------------------------------------