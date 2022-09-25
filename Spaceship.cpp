#include "Spaceship.h"
#include <iostream>

using namespace std;

Spaceship::Spaceship()
{
    playerNum = -1;
    textureRow = 0;
    textureColumn = 0;
    frameCounter = 0;
    maxFrame = 0;
    velocity = D3DXVECTOR2(0, 0);
    acceleration = D3DXVECTOR2(0, 0);
    engineForce = 0.0f;
    direction = 0.0f;
    rotationSpeed = 0.0f;
    mass = 0.0f;
    massCollided = false;
    bounceSound = new GameSound();
    collectSound = new GameSound();
}

Spaceship::~Spaceship()
{
    delete this;
}

void Spaceship::Init(int playerNum, int textureWidth, int textureHeight, int textureRow, int textureColumn,
                     int maxFrame,
                     int positionX, int positionY, float engineForce, float direction, float mass,
                     float rotationSpeed, AudioManager* audioManager)
{
    GameObject::Init(textureWidth, textureHeight, textureWidth / textureColumn, textureHeight / textureRow,
                     positionX, positionY);

    this->playerNum = playerNum;
    this->textureColumn = textureColumn;
    this->textureRow = textureRow;
    
    frameCounter = 0;
    this->maxFrame = maxFrame;
    
    displayRect.top = 0;
    displayRect.left = (playerNum - 1) * spriteWidth;
    displayRect.right = displayRect.left + spriteWidth;
    displayRect.bottom = displayRect.top + spriteHeight;
    
    velocity = D3DXVECTOR2(0, 0);
    acceleration = D3DXVECTOR2(0, 0);
    this->engineForce = engineForce;
    this->direction = direction;
    this->rotationSpeed = rotationSpeed;

    this->mass = mass;
    
    // Initialize sounds
    bounceSound->Init("Assets/Audio/bounce.mp3", 1.0, 1.0, 0.0, false);
    collectSound->Init("Assets/Audio/point-get.ogg", 1.0, 1.0, 0.0, false);
    
    bounceSound->SetSound(audioManager->CreateSounds(bounceSound->GetSoundFilePath(), bounceSound->GetLoop()));
    collectSound->SetSound(audioManager->CreateSounds(collectSound->GetSoundFilePath(), collectSound->GetLoop()));
}

// Setters
void Spaceship::SetTextureWidth(int textureWidth)
{
    this->textureWidth = textureWidth;

    // Update the sprite width and display display rect
    spriteWidth = textureWidth / textureColumn;
}

void Spaceship::SetTextureHeight(int textureHeight)
{
    this->textureHeight = textureHeight;
    
    // Update sprite height and display rect
    spriteHeight = textureHeight / textureRow;
}

void Spaceship::SetTextureRow(int texture_row)
{
    this->textureRow = texture_row;

    spriteHeight = textureHeight / texture_row;
}

void Spaceship::SetTextureColumn(int texture_column)
{
    this->textureColumn = texture_column;

    spriteWidth = textureWidth / texture_column;
}


void Spaceship::SetFrameCounter(int frame_counter)
{
    this->frameCounter = frame_counter;
}

void Spaceship::SetMaxFrame(int max_frame)
{
    this->maxFrame = max_frame;
}

void Spaceship::SetVelocity(D3DXVECTOR2 spaceShipVelocity)
{
    this->velocity = spaceShipVelocity;
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

void Spaceship::SetAcceleration(D3DXVECTOR2 spaceshipAcceleration)
{
    this->acceleration = spaceshipAcceleration;
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

void Spaceship::SetEngineForce(float engine_Force)
{
    this->engineForce = engine_Force;
}

void Spaceship::SetDirection(float spaceship_Direction)
{
    this->direction = spaceship_Direction;
}

void Spaceship::SetMass(float spaceship_Mass)
{
    this->mass = spaceship_Mass;
}

void Spaceship::SetRotationSpeed(float rotation_speed)
{
    this->rotationSpeed = rotation_speed;
}

void Spaceship::SetMassCollided(bool mass_Collided)
{
    this->massCollided = mass_Collided;
}

// Getters
int Spaceship::GetPlayerNum()
{
    return playerNum;
}

int Spaceship::GetTextureRow()
{
    return textureRow;
}

int Spaceship::GetTextureColumn()
{
    return textureColumn;
}



int Spaceship::GetFrameCounter()
{
    return frameCounter;
}

int Spaceship::GetMaxFrame()
{
    return maxFrame;
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
   return mass;
}

float Spaceship::GetRotationSpeed()
{
    return rotationSpeed;
}

bool Spaceship::GetMassCollided()
{
    return massCollided;
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
        //------------ Push spaceship out of each other---------------
        /*
         * Getting both spaceships center point (vector of the window)
         * by adding the position of the spaceship (top left of the sprite) and the center of the sprite (vector of the sprite, not window)
         */
        D3DXVECTOR2 centerPointPosition = GameObject::GetPosition() + GameObject::GetSpriteCenter();
        D3DXVECTOR2 anotherSpaceshipCenterPointPosition = anotherSpaceship->GetPosition() + anotherSpaceship->GetSpriteCenter();

        // Get the distance between the two spaceship center points
        D3DXVECTOR2 distance = centerPointPosition - anotherSpaceshipCenterPointPosition;

        /*
         * Get the overlap between the two spaceships by using the distance between the two center points and subtracting the radius of the two spaceships
         * then multiply by 0.5 to get the overlap for each spaceship
         */
        float overlap = 0.5f * (D3DXVec2Length(&distance) - (GameObject::GetSpriteWidth() / 2) - (anotherSpaceship->GetSpriteWidth() / 2));

        /*
         * Now, that we know how much they overlap, we need to translate that into a vector
         * We do this by multiplying overlap with the unit vector of the distance between the two center points
         * How to get unit vector of distance
         *  Example: Getting the x component of distance: distance.x / D3DXVec2Length(&distance)
         * Then we will get the current position and minus the overlap vector to get the new position
         * minus because we want to push this spaceship in the opposite direction of the other spaceship
         * do this for x and y component
         */
        int positionX = GetPosition().x - (overlap * distance.x / D3DXVec2Length(&distance));
        int positionY = GetPosition().y - (overlap * distance.y / D3DXVec2Length(&distance));
        
        // Similar to above, but add the overlap vector because we want to push the other spaceship in the opposite direction of this spaceship
        int anotherSpaceshipPositionX = anotherSpaceship->GetPosition().x + (overlap * distance.x / D3DXVec2Length(&distance));
        int anotherSpaceshipPositionY = anotherSpaceship->GetPosition().y + (overlap * distance.y / D3DXVec2Length(&distance));

        // Set the new position of the two spaceships
        SetPosition(positionX, positionY);
        anotherSpaceship->SetPosition(anotherSpaceshipPositionX, anotherSpaceshipPositionY);
        //------------ Push spaceship out of each other END---------------

        //------------ Calculate new velocity for both spaceships---------------
        /*
         * Getting the vector between the two center points and normalize it by dividing the length of the vector
         * Therefore, we will get the normal unit vector
         */
        float normalX = (anotherSpaceshipCenterPointPosition.x - centerPointPosition.x) / D3DXVec2Length(&distance);
        float normalY = (anotherSpaceshipCenterPointPosition.y - centerPointPosition.y) / D3DXVec2Length(&distance);

        /*
         * Get the tangential unit vector by flipping the y-axis and the x-axis of the normal unit vector
         * Tangential unit vector is perpendicular to the normal unit vector, can be proven using dot product of tangent unit vector and normal unit vector
         */
        float tangentX = -normalY;
        float tangentY = normalX;

        /*
         * Dot Product between the spaceship's velocity vector and the tangential unit vector
         * i.e. how much of the velocity vector will be transferred towards the tangential vector
         */
        float dpTangent1 = GetVelocity().x * tangentX + GetVelocity().y * tangentY;
        float dpTangent2 = anotherSpaceship->GetVelocity().x * tangentX + anotherSpaceship->GetVelocity().y * tangentY;

        
        /*
         * Dot Product between the spaceship's velocity vector and the normal unit vector
         * i.e. How much of the velocity vector will be transferred towards the normal vector
         */
        float dpNormal1 = GetVelocity().x * normalX + GetVelocity().y * normalY;
        float dpNormal2 = anotherSpaceship->GetVelocity().x * normalX + anotherSpaceship->GetVelocity().y * normalY;
        
        /*
         * One Dimensional Elastic Collision Formula, for the normal
         * Using the equation
         * v1 = m1 - m2 / m1 + m2 * v1 + 2 * m2 / m1 + m2 * v2
         * v2 = m2 - m1 / m1 + m2 * v2 + 2 * m1 / m1 + m2 * v1
         * u1 is substituted with dpNormal1 
         * u2 is substituted with dpNormal2
         * used the velocity transferred to the normal vector instead of directly using the velocity
         *
         * Note:
         * m1 and m2 are the mass of the two objects
         * u1 and u2 are the initial velocity of the two objects
         * v1 and v2 are the final velocity of the two objects
         */
        
        float v1 = (mass - anotherSpaceship->GetMass()) / (mass + anotherSpaceship->GetMass()) * dpNormal1 + 2.0f * anotherSpaceship->GetMass() / (mass + anotherSpaceship->GetMass()) * dpNormal2;
        float v2 = (anotherSpaceship->GetMass() - mass) / (mass + anotherSpaceship->GetMass()) * dpNormal2 + 2.0f * mass / (mass + anotherSpaceship->GetMass()) * dpNormal1;

        /*
         * Updating this spaceship velocity by adding together the tangential response and the normal response
         * Tangential response is the tangent unit vector multiply by the velocity transferred to the tangential vector
         * Tangential response does not need to go through the elastic collision formula because it is not the point of collision
         * Normal response is the normal unit vector multiply by the final velocity of the normal vector
         */
        float velocityX = tangentX * dpTangent1 + normalX * v1;
        float velocityY = tangentY * dpTangent1 + normalY * v1;

        // Do the same thing for the other spaceship
        float anotherSpaceshipVelocityX = tangentX * dpTangent2 + normalX * v2;
        float anotherSpaceshipVelocityY = tangentY * dpTangent2 + normalY * v2;

        // Note: By adding together the velocity vector of this spaceship and the other spaceship,
        // it should be equal to the velocity of this spaceship before collision response is calculated

        // Set the velocity of this spaceship and the other spaceship
        SetVelocity(velocityX,velocityY);
        anotherSpaceship->SetVelocity(anotherSpaceshipVelocityX, anotherSpaceshipVelocityY);
        //------------ Calculate new velocity for both spaceships END ---------------
        
        cout << "Collision detected between spaceships" << endl;
 
        // Set bounceSound to true so that the bounce sound will be played
        bounceSound->SetPlaySoundFlag(true);
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
        mass += anotherMass->GetMass();
        
        anotherMass->SetConsumed(true);
        cout << "Collision detected between spaceship and mass" << endl;
        massCollided = true;
        collectSound->SetPlaySoundFlag(true);
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

    GameObject::SetDisplayRect(leftRect, topRect);
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
        if (GameObject::GetPosition().x < 0)
        {
            GameObject::SetPositionX(0);
        }
        else
        {
            GameObject::SetPositionX(windowWidth - GameObject::GetSpriteWidth());
        }
        // Normal Vector of Line Segment
        D3DXVECTOR2 BorderSP = D3DXVECTOR2(0, 0);
        D3DXVECTOR2 BorderEP = D3DXVECTOR2(0, 600);
        D3DXVECTOR2 minus = BorderEP - BorderSP;
        D3DXVECTOR2 BorderDir = minus / D3DXVec2Length(&minus);
        
        D3DXVECTOR2 BorderNorm = D3DXVECTOR2(-BorderDir.y, BorderDir.x);
        
        D3DXVECTOR2 velocityNorm = BorderNorm * D3DXVec2Dot(&velocity, &BorderNorm);
        D3DXVECTOR2 velocityTangent = velocity - velocityNorm;
        SetVelocity(velocityTangent - velocityNorm);
        
        cout << "Collision detected between spaceship and window left or right" << endl;
        bounceSound->SetPlaySoundFlag(true);
    }

    if (GameObject::GetPosition().y < 0 || GameObject::GetPosition().y > windowHeight - GameObject::GetSpriteHeight())
    {
        if (GameObject::GetPosition().y < 0)
        {
            GameObject::SetPositionY(0);
        }
        else
        {
            GameObject::SetPositionY(windowHeight - GameObject::GetSpriteHeight());
        }
        
        // Normal Vector of Line Segment
        D3DXVECTOR2 BorderSP = D3DXVECTOR2(0, 0);
        D3DXVECTOR2 BorderEP = D3DXVECTOR2(800, 0);
        D3DXVECTOR2 minus = BorderEP - BorderSP;
        D3DXVECTOR2 BorderDir = minus / D3DXVec2Length(&minus);
        
        D3DXVECTOR2 BorderNorm = D3DXVECTOR2(BorderDir.y, -BorderDir.x);

        D3DXVECTOR2 velocityNorm = BorderNorm * D3DXVec2Dot(&velocity, &BorderNorm);
        D3DXVECTOR2 velocityTangent = velocity - velocityNorm;
        SetVelocity(velocityTangent - velocityNorm);
        
        bounceSound->SetPlaySoundFlag(true);
        std::cout << "Collision detected between spaceship and top or bottom" << endl;
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
        acceleration.x = sin(direction) * engineForce / mass;
        acceleration.y = -cos(direction) * engineForce / mass;
    }

    if (goBackward)
    {
        // calculate the acceleration of the spaceship
        // a = F / m
        acceleration.x = -sin(direction) * engineForce / mass;
        acceleration.y = cos(direction) * engineForce / mass;
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

void Spaceship::AlterSoundPan()
{
    bounceSound->SetPan((GetPosition().x - 400) / 400);
    collectSound->SetPan((GetPosition().x - 400) / 400);
}


void Spaceship::Update(bool turnLeft, bool turnRight, bool goForward, bool goBackward, float friction,
                       Spaceship* anotherSpaceship, std::vector<Mass*>* masses, int windowWidth, int windowHeight)
{
    Move(turnLeft, turnRight, goForward, goBackward, friction);
    CollisionSpaceship(anotherSpaceship);

    for (int i = 0; i < masses->size(); i++)
    {
        CollisionMass(masses->at(i));
    }
    
    WindowBounce(windowWidth, windowHeight);
    
    NextFrame(this->playerNum);

    AlterSoundPan();
}

void Spaceship::Draw(LPD3DXSPRITE spriteBrush)
{
    D3DXMatrixTransformation2D(&matrix, NULL, 0.5f, &scaling,
                               &spriteCenter, direction, &position);
    spriteBrush->SetTransform(&matrix);

    HRESULT hr = spriteBrush->Draw(objectTexture, &displayRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
    if (FAILED(hr))
    {
        std::cout << "Draw Failed." << endl;
    }
}


// Method to play the sound for the spaceship
void Spaceship::PlaySounds(AudioManager* audioManager)
{
    /*
     * If the spaceship is colliding with another spaceship, then play the bounce sound
     */
    if (bounceSound->GetPlaySoundFlag())
    {
        audioManager->PlaySoundEffect(bounceSound->GetSound(), bounceSound->GetVolume(), bounceSound->GetPitch(), bounceSound->GetPan());
        bounceSound->SetPlaySoundFlag(false);
    }

    /*
     * If the spaceship is colliding with a mass, then play the point get sound
     */
    if (collectSound->GetPlaySoundFlag())
    {
        audioManager->PlaySoundEffect(collectSound->GetSound(), collectSound->GetVolume(), collectSound->GetPitch(), collectSound->GetPan());
        collectSound->SetPlaySoundFlag(false);
    }
}

void Spaceship::CleanUp()
{
    bounceSound->CleanUp();
    collectSound->CleanUp();

    bounceSound = nullptr;
    collectSound = nullptr;
    
    GameObject::CleanUp();
}
