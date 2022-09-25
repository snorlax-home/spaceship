#include "Spaceship.h"
#include <iostream>

using namespace std;

Spaceship::Spaceship()
{
    // Initialize the zero values for the variables
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
    textureRedValue = 255;
    textureGreenValue = 255;
    textureBlueValue = 255;
    textureColor = D3DCOLOR_XRGB(textureRedValue, textureGreenValue, textureBlueValue);
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
    // Use parent class Init to assign values to variables in parent class
    GameObject::Init(textureWidth, textureHeight, textureWidth / textureColumn, textureHeight / textureRow,
                     positionX, positionY);

    // Assign values to variables in this class
    this->playerNum = playerNum;
    this->textureColumn = textureColumn;
    this->textureRow = textureRow;

    // Frame counter set to 0 to let it start from the first frame
    frameCounter = 0;
    this->maxFrame = maxFrame;

    // displayRect starts from the top, alter left to get the correct spaceship sprite
    displayRect.top = 0;
    displayRect.left = (playerNum - 1) * spriteWidth;

    // Simply add the sprite width to the left to get the right of the displayRect
    displayRect.right = displayRect.left + spriteWidth;

    // Simply add the sprite height to the top to get the bottom of the displayRect
    displayRect.bottom = displayRect.top + spriteHeight;
    
    this->engineForce = engineForce;
    this->direction = direction;
    this->rotationSpeed = rotationSpeed;

    this->mass = mass;
    
    /* Initialize sounds
    * Init(fileName, loop, volume, pan, loop)
    * Initialize GameSound with default values, not altering volume, pitch, pan
    * sound will also not be looped
    */
    bounceSound->Init("Assets/Audio/bounce.mp3", 1.0, 1.0, 0.0, false);
    collectSound->Init("Assets/Audio/point-get.ogg", 1.0, 1.0, 0.0, false);

    /*
     * Use audioManager to create a Sound Object
     * assigned the pointer into GameSound object
     */
    bounceSound->SetSound(audioManager->CreateSounds(bounceSound->GetSoundFilePath(), bounceSound->GetLoop()));
    collectSound->SetSound(audioManager->CreateSounds(collectSound->GetSoundFilePath(), collectSound->GetLoop()));
}

// Setters
// Set the texture width
void Spaceship::SetTextureWidth(int textureWidth)
{
    this->textureWidth = textureWidth;

    // Update the sprite width and display display rect
    spriteWidth = textureWidth / textureColumn;
    displayRect.right = displayRect.left + spriteWidth;
}

void Spaceship::SetTextureHeight(int textureHeight)
{
    this->textureHeight = textureHeight;
    
    // Update sprite height and display rect
    spriteHeight = textureHeight / textureRow;
    displayRect.bottom = displayRect.top + spriteHeight;
}

void Spaceship::SetTextureRow(int texture_row)
{
    this->textureRow = texture_row;

    // Update sprite height and display rect
    spriteHeight = textureHeight / texture_row;
    displayRect.bottom = displayRect.top + spriteHeight;
}

void Spaceship::SetTextureColumn(int texture_column)
{
    this->textureColumn = texture_column;

    // Update sprite width and display rect
    spriteWidth = textureWidth / texture_column;
    displayRect.right = displayRect.left + spriteWidth;
}

// Set the frame counter
void Spaceship::SetFrameCounter(int frame_counter)
{
    this->frameCounter = frame_counter;
}

// Set the max frame
void Spaceship::SetMaxFrame(int max_frame)
{
    this->maxFrame = max_frame;
}

// Set the velocity using a D3DXVECTOR2
void Spaceship::SetVelocity(D3DXVECTOR2 spaceShipVelocity)
{
    this->velocity = spaceShipVelocity;
}

// Set the velocity using x and y values
void Spaceship::SetVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}

// Set velocity.x
void Spaceship::SetVelocityX(float x)
{
    velocity.x = x;
}

// Set velocity.y
void Spaceship::SetVelocityY(float y)
{
    velocity.y = y;
}

// Set the acceleration using a D3DXVECTOR2
void Spaceship::SetAcceleration(D3DXVECTOR2 spaceshipAcceleration)
{
    this->acceleration = spaceshipAcceleration;
}

// Set the acceleration using x and y values
void Spaceship::SetAcceleration(float x, float y)
{
    acceleration.x = x;
    acceleration.y = y;
}

// Set acceleration.x
void Spaceship::SetAccelerationX(float x)
{
    acceleration.x = x;
}

// Set acceleration.y
void Spaceship::SetAccelerationY(float y)
{
    acceleration.y = y;
}

// Set the engine force
void Spaceship::SetEngineForce(float engine_Force)
{
    this->engineForce = engine_Force;
}

// Set the direction of the spaceship
void Spaceship::SetDirection(float spaceship_Direction)
{
    this->direction = spaceship_Direction;
}

// Set the mass of the spaceship
void Spaceship::SetMass(float spaceship_Mass)
{
    this->mass = spaceship_Mass;
}

// Set the rotation speed of the spaceship
void Spaceship::SetRotationSpeed(float rotation_speed)
{
    this->rotationSpeed = rotation_speed;
}

// Set the texture color
void Spaceship::SetMassCollided(bool mass_Collided)
{
    this->massCollided = mass_Collided;
}

// Getters
// Get the player number
int Spaceship::GetPlayerNum()
{
    return playerNum;
}

// Get the texture row
int Spaceship::GetTextureRow()
{
    return textureRow;
}

// Get the texture column
int Spaceship::GetTextureColumn()
{
    return textureColumn;
}

// Get the frame counter
int Spaceship::GetFrameCounter()
{
    return frameCounter;
}

// Get the max frame
int Spaceship::GetMaxFrame()
{
    return maxFrame;
}

// Get the velocity
D3DXVECTOR2 Spaceship::GetVelocity()
{
    return velocity;
}

// Get the acceleration
D3DXVECTOR2 Spaceship::GetAcceleration()
{
    return acceleration;
}

// Get the direction of the spaceship
float Spaceship::GetDirection()
{
    return direction;
}

//Get the engine force
float Spaceship::GetEngineForce()
{
    return engineForce;
}

// Get the mass of the spaceship
float Spaceship::GetMass()
{
   return mass;
}

// Get the rotation speed of the spaceship
float Spaceship::GetRotationSpeed()
{
    return rotationSpeed;
}

// Get the mass collided flag
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

        this->textureGreenValue = 5;
        this->textureBlueValue = 5;
        anotherSpaceship->textureGreenValue = 5;
        anotherSpaceship->textureBlueValue = 5;
        this->textureColor = D3DCOLOR_XRGB(this->textureRedValue, this->textureGreenValue, this->textureBlueValue);
        anotherSpaceship->textureColor = D3DCOLOR_XRGB(anotherSpaceship->textureRedValue, anotherSpaceship->textureGreenValue, anotherSpaceship->textureBlueValue);
    }
}

void Spaceship::CollisionMass(Mass* anotherMass)
{
    /*
     * Check if the spaceship is colliding with a mass
     * If yes, increase mass of the spaceship by using the mass of the mass object
     * then, set mass object consumed flag to true to make it disappear
     */
    if (CircleCollisionDetection(anotherMass->GetSpriteWidth() / 2,
                                 anotherMass->GetPosition() + anotherMass->GetSpriteCenter()))
    {
        mass += anotherMass->GetMass();
        
        anotherMass->SetConsumed(true);
        cout << "Collision detected between spaceship and mass" << endl;

        // Set it to true so that can be used to checking points
        massCollided = true;

        // Set collectSound playSoundFlag to true so that the collect sound will be played
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
    /*
     * Alter the pan of the sound based on the position of the spaceship
     * Will update the pan dynamically
     * The pan will be -1 if the spaceship is at the very left side of the screen
     * The pan will be 1 if the spaceship is at the very right side of the screen
     * if the spaceship is at the middle of the screen, the pan will be 0
     * E.g. if the spaceship is at 200 pixels from the left side of the screen, the pan will be -0.5
     * if the spaceship is at 600 pixels from the left side of the screen, the pan will be 0.5
     */
    bounceSound->SetPan((GetPosition().x - 400) / 400);
    collectSound->SetPan((GetPosition().x - 400) / 400);
}


void Spaceship::Update(bool turnLeft, bool turnRight, bool goForward, bool goBackward, float friction,
                       Spaceship* anotherSpaceship, std::vector<Mass*>* masses, int windowWidth, int windowHeight)
{
    // Update the spaceship based on the input
    Move(turnLeft, turnRight, goForward, goBackward, friction);

    // Collision detection and response between spaceship and another spaceship
    CollisionSpaceship(anotherSpaceship);

    // Collision detection and response between spaceship and mass
    for (int i = 0; i < masses->size(); i++)
    {
        CollisionMass(masses->at(i));
    }

    // Collision detection and response between spaceship and window
    WindowBounce(windowWidth, windowHeight);

    // Update the animation of the spaceship
    NextFrame(this->playerNum);

    // Update the pan of the sound effects based on the position of the ship
    AlterSoundPan();

    if (this->textureGreenValue < 255 || anotherSpaceship->textureGreenValue < 255)
    {
        this->textureGreenValue += 2;
        this->textureBlueValue += 2;
        anotherSpaceship->textureGreenValue += 2;
        anotherSpaceship->textureBlueValue += 2;
    }
    this->textureColor = D3DCOLOR_XRGB(255, textureGreenValue, textureBlueValue);
    anotherSpaceship->textureColor = D3DCOLOR_XRGB(255, textureGreenValue, textureBlueValue);
}

void Spaceship::Draw(LPD3DXSPRITE spriteBrush)
{
    D3DXMatrixTransformation2D(&matrix, NULL, 0.5f, &scaling,
                               &spriteCenter, direction, &position);
    spriteBrush->SetTransform(&matrix);

    HRESULT hr = spriteBrush->Draw(objectTexture, &displayRect, NULL, NULL, textureColor);
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
        // Reset the play sound flag so that the sound will not be played again until the spaceship collides with another spaceship or window
        bounceSound->SetPlaySoundFlag(false);
    }

    /*
     * If the spaceship is colliding with a mass, then play the point get sound
     */
    if (collectSound->GetPlaySoundFlag())
    {
        audioManager->PlaySoundEffect(collectSound->GetSound(), collectSound->GetVolume(), collectSound->GetPitch(), collectSound->GetPan());
        // Reset the play sound flag so that the sound will not be played again until the spaceship collides with another mass
        collectSound->SetPlaySoundFlag(false);
    }
}

// Clean up the spaceship object
void Spaceship::CleanUp()
{
    // Clean up the sounds
    bounceSound->CleanUp();
    collectSound->CleanUp();

    // Assign NULL to the pointers
    bounceSound = nullptr;
    collectSound = nullptr;

    // Call the clean up method of the GameObject class
    GameObject::CleanUp();
}
