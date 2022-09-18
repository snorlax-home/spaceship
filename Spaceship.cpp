#include "Spaceship.h"
#include <iostream>

using namespace std;

void Spaceship::Init(int playerNum, int textureWidth, int textureHeight, int textureRow, int textureColumn,
                     int spriteFPS, int maxFrame,
                     float positionX, float positionY, float engineForce, float direction, float mass,
                     float rotationSpeed)
{
    GameObject::Init('S', textureWidth, textureHeight, textureWidth / textureColumn, textureHeight / textureRow,
                     positionX, positionY, mass);

    this->playerNum = playerNum;
    this->textureColumn = textureColumn;
    this->textureRow = textureRow;

    this->spriteFPS = spriteFPS;
    frameCounter = 0;
    this->maxFrame = maxFrame;

    InitDisplayRect();

    velocity = D3DXVECTOR2(0, 0);
    acceleration = D3DXVECTOR2(0, 0);
    this->engineForce = engineForce;
    this->direction = direction;
    this->rotationSpeed = rotationSpeed;

    // 	Set all collide flags to false
    bool spaceshipCollided = false;
    bool massCollided = false;
    bool wallCollided = false;

    // Initialize and load spaceship AudioManager
    spaceshipAudioManager = new SpaceshipAudioManager();
    spaceshipAudioManager->InitializeAudio();
    spaceshipAudioManager->LoadSounds();
}

// Setters
void Spaceship::SetTextureWidth(int textureWidth)
{
    GameObject::SetTextureWidth(textureWidth);

    // Update the sprite width and display display rect
    GameObject::SetSpriteWidth(GameObject::GetTextureWidth() / textureColumn);
}

void Spaceship::SetTextureHeight(int textureHeight)
{
    GameObject::SetTextureHeight(textureHeight);

    // Update sprite height and display rect
    GameObject::SetSpriteHeight(GameObject::GetTextureHeight() / textureRow);
}

void Spaceship::SetTextureRow(int textureRow)
{
    this->textureRow = textureRow;

    GameObject::SetSpriteHeight(GameObject::GetTextureHeight() / textureRow);
}

void Spaceship::SetTextureColumn(int textureColumn)
{
    this->textureColumn = textureColumn;

    GameObject::SetSpriteWidth(GameObject::GetTextureWidth() / textureColumn);
}

void Spaceship::SetScaling(float scalingX, float scalingY)
{
    GameObject::SetScaling(scalingX, scalingY);
}

void Spaceship::SetSpriteFPS(int spriteFPS)
{
    this->spriteFPS = spriteFPS;
}

void Spaceship::SetFrameCounter(int frameCounter)
{
    this->frameCounter = frameCounter;
}

void Spaceship::SetMaxFrame(int maxFrame)
{
    this->maxFrame = maxFrame;
}

void Spaceship::SetPosition(D3DXVECTOR2 position)
{
    GameObject::SetPosition(position);
}

void Spaceship::SetPosition(float x, float y)
{
    GameObject::SetPosition(x, y);
}

void Spaceship::SetPositionX(float x)
{
    GameObject::SetPositionX(x);
}

void Spaceship::SetPositionY(float y)
{
    GameObject::SetPositionY(y);
}

void Spaceship::SetVelocity(D3DXVECTOR2 velocity)
{
    this->velocity = velocity;
}

void Spaceship::SetVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}

void Spaceship::SetVelocityX(float x)
{
    velocity.x = x;
}

void Spaceship::SetVelocityY(float y)
{
    velocity.y = y;
}

void Spaceship::SetAcceleration(D3DXVECTOR2 acceleration)
{
    this->acceleration = acceleration;
}

void Spaceship::SetAcceleration(float x, float y)
{
    acceleration.x = x;
    acceleration.y = y;
}

void Spaceship::SetAccelerationX(float x)
{
    acceleration.x = x;
}

void Spaceship::SetAccelerationY(float y)
{
    acceleration.y = y;
}

void Spaceship::SetEngineForce(float engineForce)
{
    this->engineForce = engineForce;
}

void Spaceship::SetDirection(float direction)
{
    this->direction = direction;
}

void Spaceship::SetMass(float mass)
{
    GameObject::SetMass(mass);
}

void Spaceship::SetRotationSpeed(float rotationSpeed)
{
    this->rotationSpeed = rotationSpeed;
}

void Spaceship::SetSpaceshipCollided(bool spaceshipCollided)
{
    this->spaceshipCollided = spaceshipCollided;
}

void Spaceship::SetMassCollided(bool massCollided)
{
    this->massCollided = massCollided;
}

void Spaceship::SetWallCollided(bool wallCollided)
{
    this->wallCollided = wallCollided;
}

// Getters
int Spaceship::GetPlayerNum()
{
    return playerNum;
}

int Spaceship::GetTextureWidth()
{
    return GameObject::GetTextureWidth();
}

int Spaceship::GetTextureHeight()
{
    return GameObject::GetTextureHeight();
}

int Spaceship::GetTextureRow()
{
    return textureRow;
}

int Spaceship::GetTextureColumn()
{
    return textureColumn;
}

int Spaceship::GetSpriteWidth()
{
    return GameObject::GetSpriteWidth();
}

int Spaceship::GetSpriteHeight()
{
    return GameObject::GetSpriteHeight();
}

D3DXVECTOR2 Spaceship::GetSpriteCenter()
{
    return GameObject::GetSpriteCenter();
}

D3DXVECTOR2* Spaceship::GetSpriteCenterAddress()
{
    return GameObject::GetSpriteCenterAddress();
}

D3DXVECTOR2 Spaceship::GetScaling()
{
    return GameObject::GetScaling();
}

D3DXVECTOR2* Spaceship::GetScalingAddress()
{
    return GameObject::GetScalingAddress();
}

int Spaceship::GetSpriteFPS()
{
    return spriteFPS;
}

int Spaceship::GetFrameCounter()
{
    return frameCounter;
}

int Spaceship::GetMaxFrame()
{
    return maxFrame;
}

RECT Spaceship::GetDisplayRect()
{
    return GameObject::GetDisplayRect();
}

RECT* Spaceship::GetDisplayRectAddress()
{
    return GameObject::GetDisplayRectAddress();
}

D3DXVECTOR2 Spaceship::GetPosition()
{
    return GameObject::GetPosition();
}

D3DXVECTOR2* Spaceship::GetPositionAddress()
{
    return GameObject::GetPositionAddress();
}

D3DXVECTOR2 Spaceship::GetVelocity()
{
    return velocity;
}

D3DXVECTOR2 Spaceship::GetAcceleration()
{
    return acceleration;
}

float Spaceship::GetDirection()
{
    return direction;
}

float Spaceship::GetEngineForce()
{
    return engineForce;
}

float Spaceship::GetMass()
{
    return GameObject::GetMass();
}

float Spaceship::GetRotationSpeed()
{
    return rotationSpeed;
}

bool Spaceship::GetSpaceshipCollided()
{
    return spaceshipCollided;
}

bool Spaceship::GetMassCollided()
{
    return massCollided;
}

bool Spaceship::GetWallCollided()
{
    return wallCollided;
}

void Spaceship::InitDisplayRect()
{
    int rectTop = 0;
    int rectLeft = (playerNum - 1) * GameObject::GetSpriteWidth();
    int rectRight = rectLeft + GameObject::GetSpriteWidth();
    int rectBottom = rectTop + GameObject::GetSpriteHeight();

    GameObject::SetDisplayRect(rectTop, rectLeft, rectRight, rectBottom);
}

// Game methods
// Method to check for collision between two objects
bool Spaceship::CircleCollisionDetection(int radiusB, D3DXVECTOR2 positionB)
{
    // Get the radius of the spaceship by dividing the width of the sprite by 2
    int radiusA = GameObject::GetSpriteWidth() / 2;

    // Get the distance between midpoint of the spaceship and the other object
    // add SpriteCenter to get midpoint of spaceship
    D3DXVECTOR2 distance = GameObject::GetPosition() + GameObject::GetSpriteCenter() - positionB;

    /*
     * Check if the distance between the two objects is less than the sum of the radius of the two objects
     * If it is, then the two objects are colliding
     * If it is not, then the two objects are not colliding
     */
    if (radiusA + radiusB < D3DXVec2Length(&distance))
    {
        return false;
    }
    else
    {
        cout << "Collision detected!" << endl;
        return true;
    }
}

void Spaceship::CollisionSpaceship(Spaceship* anotherSpaceship)
{
    /*
     * Check if the spaceship is colliding with another spaceship
     * If yes, then set velocity of both spaceship to be 1.2 and opposite direction
     * then, set the spaceshipCollided to true
     */
    if (CircleCollisionDetection(anotherSpaceship->GetSpriteWidth() / 2,
                                 anotherSpaceship->GetPosition() + anotherSpaceship->GetSpriteCenter()))
    {
        velocity.x *= -1.2;
        velocity.y *= -1.2;

        anotherSpaceship->SetVelocityX(-velocity.x);
        anotherSpaceship->SetVelocityY(-velocity.y);
        cout << "Collision detected between spaceships" << endl;
        spaceshipCollided = true;
    }
}

void Spaceship::CollisionMass(Mass* anotherMass)
{
    /*
     * Check if the spaceship is colliding with a mass
     * If yes, increase mass of the spaceship by using the mass of the mass object
     * then, trigger mass object Consumed() method and set massCollided to true
     */
    if (CircleCollisionDetection(anotherMass->GetSpriteWidth() / 2,
                                 anotherMass->GetPosition() + anotherMass->GetSpriteCenter()))
    {
        GameObject::SetMass(GameObject::GetMass() + anotherMass->GetMass());

        anotherMass->Consumed();
        cout << "Collision detected between spaceship and mass" << endl;
        massCollided = true;
    }
}

void Spaceship::NextFrame(int playerNumber)
{
    frameCounter++;

    if (frameCounter > maxFrame)
    {
        frameCounter = 0;
    }

    int leftRect = (playerNum - 1) * GameObject::GetSpriteWidth();
    int topRect = frameCounter * GameObject::GetSpriteHeight();
    int rightRect = leftRect + GameObject::GetSpriteWidth();
    int bottomRect = topRect + GameObject::GetSpriteHeight();

    GameObject::SetDisplayRect(leftRect, topRect, rightRect, bottomRect);
}

void Spaceship::WindowBounce(int windowWidth, int windowHeight)
{
    /*
     * Check if the spaceship is colliding with the window
     * If yes, then set velocity of the spaceship to be 1.2 and opposite direction
     * then, set the wallCollided to true
     */
    if (GameObject::GetPosition().x < 0 || GameObject::GetPosition().x > windowWidth - GameObject::GetSpriteWidth())
    {
        velocity.x *= -1.2;
        wallCollided = true;
    }
    if (GameObject::GetPosition().y < 0 || GameObject::GetPosition().y > windowHeight - GameObject::GetSpriteHeight())
    {
        velocity.y *= -1.2;
        wallCollided = true;
    }
}

void Spaceship::Move(bool turnLeft, bool turnRight, bool goForward, bool goBackward, float friction)
{
    // turnLeft is true, then rotate the spaceship to the left
    if (turnLeft)
    {
        direction -= rotationSpeed;
    }

    // turnRight is true, then rotate the spaceship to the right
    if (turnRight)
    {
        direction += rotationSpeed;
    }

    // goForward is true, then accelerate the spaceship
    if (goForward)
    {
        // Calculate the acceleration of the spaceship
        // a = F / m
        acceleration.x = sin(direction) * engineForce / GameObject::GetMass();
        acceleration.y = -cos(direction) * engineForce / GameObject::GetMass();
    }

    if (goBackward)
    {
        // calculate the acceleration of the spaceship
        // a = F / m
        acceleration.x = -sin(direction) * engineForce / GameObject::GetMass();
        acceleration.y = cos(direction) * engineForce / GameObject::GetMass();
    }

    // Update velocity
    velocity += acceleration;

    // Apply friction
    velocity *= (1 - friction);

    // Update position
    GameObject::SetPosition(GameObject::GetPosition() + velocity);

    // Reset acceleration
    acceleration.x = 0;
    acceleration.y = 0;
}

void Spaceship::Update(bool turnLeft, bool turnRight, bool goForward, bool goBackward, float friction,
                       Spaceship* anotherSpaceship, Mass* massArray[], int arraySize, int windowWidth, int windowHeight)
{
    Move(turnLeft, turnRight, goForward, goBackward, friction);
    CollisionSpaceship(anotherSpaceship);
    for (int i = 0; i < arraySize; i++)
    {
        CollisionMass(massArray[i]);
    }
    WindowBounce(windowWidth, windowHeight);

    // NextFrame(this->playerNum);
}

void Spaceship::Draw(LPD3DXSPRITE spriteBrush, LPDIRECT3DTEXTURE9 texture)
{
    D3DXMatrixTransformation2D(this->GetMatrixAddress(), NULL, 0.5f, this->GetScalingAddress(),
                               this->GetSpriteCenterAddress(), this->GetDirection(), this->GetPositionAddress());
    spriteBrush->SetTransform(this->GetMatrixAddress());

    HRESULT hr = spriteBrush->Draw(texture, GetDisplayRectAddress(), NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
    if (FAILED(hr))
    {
        std::cout << "Draw Failed." << endl;
    }
}

// Method to play the sound for the spaceship
void Spaceship::SpaceshipPlaySound()
{
    // Update sound system
    spaceshipAudioManager->UpdateSound();

    /*
     * If the spaceship is colliding with another spaceship, then play the bounce sound
     */

    if (spaceshipCollided)
    {
        spaceshipAudioManager->playBounceSound();
        spaceshipCollided = false;
    }

    /*
     * If the spaceship is colliding with a mass, then play the point get sound
     */
    if (massCollided)
    {
        spaceshipAudioManager->playPointSound();
        massCollided = false;
    }

    /*
     * If the spaceship is colliding with the wall, then play the bounce sound
     */
    if (wallCollided)
    {
        spaceshipAudioManager->playBounceSound();
        wallCollided = false;
    }
}
