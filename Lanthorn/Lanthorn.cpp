#include <SDL2/SDL.h>

#include <SDL_ttf.h>

#include <SDL_image.h>

#include <iostream>

#include <filesystem>
#include <cstdlib>
#include <ctime>

#include <vector>
#include <algorithm>

bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    return (
        a.x < b.x + b.w &&
        a.x + a.w > b.x &&
        a.y < b.y + b.h &&
        a.y + a.h > b.y
        );
}

int main(int argc, char* argv[])
{  

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Current folder: "
        << std::filesystem::current_path()
        << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL failed to start: "
            << SDL_GetError()
            << std::endl;

        return 1;
    }

    if (TTF_Init() != 0)
    {
        std::cout << "TTF failed to start: "
            << TTF_GetError()
            << std::endl;

        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Lanthorn",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        SDL_WINDOW_FULLSCREEN_DESKTOP
    );

    if (window == nullptr)
    {
        std::cout << "Window failed to open: "
            << SDL_GetError()
            << std::endl;

        SDL_Quit();

        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_RenderSetLogicalSize(
        renderer,
        1280,
        720
    );

    SDL_Texture* darknessTexture =
        SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            1280,
            720
        );

    SDL_SetTextureBlendMode(
        darknessTexture,
        SDL_BLENDMODE_BLEND
    );

    // LOAD PLAYER IMAGE HERE

    std::cout << "Looking for assets/WalkingDown-Sheet.png" << std::endl;

    SDL_Surface* playerDownSurface = IMG_Load("C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/DownV1-Sheet.png"
    );

    if (playerDownSurface == nullptr)
    {
        std::cout << "IMG_Load failed: "
            << IMG_GetError()
            << std::endl;
    }
    else
    {
        std::cout << "Player image loaded successfully!"
            << std::endl;
    }

    SDL_Surface* playerDownLanternSurface =
        IMG_Load(
            "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/DownLantern.png"
        );

    SDL_Texture* playerDownLanternTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerDownLanternSurface
        );

    SDL_FreeSurface(playerDownLanternSurface);

    SDL_Texture* backgroundTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/GrassBackground.png"
    );

    if (backgroundTexture == nullptr)
    {
        std::cout << "Background failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* hotbarTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/Hotbar.png"
    );

    if (hotbarTexture == nullptr)
    {
        std::cout << "Hotbar failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* hotbarHighlightTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/HighlightSheet.png"
    );

    if (hotbarHighlightTexture == nullptr)
    {
        std::cout << "Hotbar highlight failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* lanternTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/LanternSheetV1.png"
    );

    if (lanternTexture == nullptr)
    {
        std::cout << "Lantern failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* dayClockTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/DayClockWindow-Sheet.png"
    );

    if (dayClockTexture == nullptr)
    {
        std::cout << "Day clock failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* heartTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/HeartSheet.png"
    );

    if (heartTexture == nullptr)
    {
        std::cout << "Heart sheet failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* flameTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/Flames-Sheet.png"
    );

    if (flameTexture == nullptr)
    {
        std::cout << "Flame sheet failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* fireballTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/Fireball-Sheet.png"
    );

    if (fireballTexture == nullptr)
    {
        std::cout << "Fireball failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* batDownTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/BatDown-Sheet.png"
    );

    SDL_Texture* batLeftTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/BatLeft-Sheet.png"
    );

    SDL_Texture* batUpTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/BatUp-Sheet.png"
    );

    SDL_Texture* batRightTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/BatRight-Sheet.png"
    );

    SDL_Texture* pickaxeTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/Pick-Sheet.png"
    );

    if (pickaxeTexture == nullptr)
    {
        std::cout << "Pickaxe failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* axeTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/Axe-Sheet.png"
    );

    if (axeTexture == nullptr)
    {
        std::cout << "Axe failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* cypressTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/Cypress.png"
    );

    SDL_Texture* cypressLeftTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/CypressLeft-Sheet.png"
    );

    SDL_Texture* cypressRightTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/CypressRight-Sheet.png"
    );

    SDL_Texture* cypressStumpTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/CypressStump.png"
    );

    if (cypressTexture == nullptr)
    {
        std::cout << "Cypress failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    if (cypressLeftTexture == nullptr)
    {
        std::cout << "Cypress left failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    if (cypressRightTexture == nullptr)
    {
        std::cout << "Cypress right failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    if (cypressStumpTexture == nullptr)
    {
        std::cout << "Cypress stump failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* deadTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/Dead.png"
    );

    SDL_Texture* deadLeftTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/DeadLeft-Sheet.png"
    );

    SDL_Texture* deadRightTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/DeadRight-Sheet.png"
    );

    SDL_Texture* deadStumpTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/DeadStump.png"
    );

    if (deadTexture == nullptr)
    {
        std::cout << "Dead tree failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    if (deadLeftTexture == nullptr)
    {
        std::cout << "Dead left failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    if (deadRightTexture == nullptr)
    {
        std::cout << "Dead right failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    if (deadStumpTexture == nullptr)
    {
        std::cout << "Dead stump failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Rect hotbarRect;

    hotbarRect.w = 656;
    hotbarRect.h = 128;

    hotbarRect.x = (1280 - hotbarRect.w) / 2;
    hotbarRect.y = 720 - hotbarRect.h - 20;

    SDL_Rect lanternSourceRect;

    lanternSourceRect.x = 0;
    lanternSourceRect.y = 0;
    lanternSourceRect.w = 568;
    lanternSourceRect.h = 56;

    SDL_Rect lanternRect;

    lanternRect.w = 568;
    lanternRect.h = 56;

    lanternRect.x = hotbarRect.x + 40;
    lanternRect.y = hotbarRect.y + 40;

    SDL_Rect pickaxeSourceRect;

    pickaxeSourceRect.x = 0;
    pickaxeSourceRect.y = 0;
    pickaxeSourceRect.w = 568;
    pickaxeSourceRect.h = 56;

    SDL_Rect pickaxeRect;

    pickaxeRect.w = 568;
    pickaxeRect.h = 56;

    pickaxeRect.x = hotbarRect.x + 40;
    pickaxeRect.y = hotbarRect.y + 40;

    SDL_Rect axeSourceRect;

    axeSourceRect.x = 0;
    axeSourceRect.y = 0;
    axeSourceRect.w = 568;
    axeSourceRect.h = 56;

    SDL_Rect axeRect;

    axeRect.w = 568;
    axeRect.h = 56;

    axeRect.x = hotbarRect.x + 40;
    axeRect.y = hotbarRect.y + 40;
    const int TREE_COUNT = 6000;

    SDL_Rect treeRects[TREE_COUNT];
    SDL_Rect treeCollisionRects[TREE_COUNT];

    SDL_Rect stumpCollisionRects[TREE_COUNT];

    int treeTypes[TREE_COUNT];
    bool treeFlipped[TREE_COUNT];

    int treeHits[TREE_COUNT] = {};
    bool treeFalling[TREE_COUNT] = {};
    bool treeFallen[TREE_COUNT] = {};
    int treeFallFrame[TREE_COUNT] = {};

    int treeFallDirection[TREE_COUNT] = {};
    bool treeRandomFall[TREE_COUNT] = {};

    SDL_Rect playerSpawnRect;

    playerSpawnRect.x = 615;
    playerSpawnRect.y = 335;
    playerSpawnRect.w = 96;
    playerSpawnRect.h = 96;

    const int treeTileSize = 128;
    const int treeMapOffsetX = 640 - (50 * treeTileSize);
    const int treeMapOffsetY = 360 - (50 * treeTileSize);

    for (int i = 0; i < TREE_COUNT; i++)
    {
        bool validPosition = false;

        int attempts = 0;

        while (!validPosition && attempts < 1000)
        {
            attempts++;
        
            treeRects[i].w = 140;
            treeRects[i].h = 356;
            int treeTileX = std::rand() % 100;
            int treeTileY = std::rand() % 100;

            int tileWorldX =
                treeMapOffsetX + treeTileX * treeTileSize;

            int tileWorldY =
                treeMapOffsetY + treeTileY * treeTileSize;

            treeRects[i].x = tileWorldX - 8;
            treeRects[i].y = tileWorldY - 264;

            validPosition = true;

            float treeDx = treeTileX - 49.5f;
            float treeDy = treeTileY - 49.5f;

            if ((treeDx * treeDx) + (treeDy * treeDy) > 50.0f * 50.0f)
            {
                validPosition = false;
            }

            // Do not spawn on the player.
            if (CheckCollision(treeRects[i], playerSpawnRect))
            {
                validPosition = false;
            }

            treeCollisionRects[i].w = 96;
            treeCollisionRects[i].h = 96;

            treeCollisionRects[i].x =
                treeRects[i].x +
                (treeRects[i].w - treeCollisionRects[i].w) / 2;

            treeCollisionRects[i].y =
                treeRects[i].y +
                treeRects[i].h -
                treeCollisionRects[i].h;

            // Do not spawn on another tree.
            for (int j = 0; j < i; j++)
            {
                if (CheckCollision(treeCollisionRects[i], treeCollisionRects[j]))
                {
                    validPosition = false;
                    break;
                }
            }
        }

        treeTypes[i] = std::rand() % 2;
        treeFlipped[i] = std::rand() % 2;


        treeCollisionRects[i].w = 96;
        treeCollisionRects[i].h = 96;

        treeCollisionRects[i].x =
            treeRects[i].x +
            (treeRects[i].w - treeCollisionRects[i].w) / 2;

        treeCollisionRects[i].y =
            treeRects[i].y +
            treeRects[i].h -
            treeCollisionRects[i].h;
    
        stumpCollisionRects[i].w = 96;
        stumpCollisionRects[i].h = 56;

        stumpCollisionRects[i].x =
            treeRects[i].x +
            (treeRects[i].w - stumpCollisionRects[i].w) / 2;

        stumpCollisionRects[i].y =
            treeRects[i].y +
            treeRects[i].h -
            stumpCollisionRects[i].h;
    
    }

    SDL_Rect hotbarHighlightSource;

    hotbarHighlightSource.x = 0;
    hotbarHighlightSource.y = 0;
    hotbarHighlightSource.w = 72;
    hotbarHighlightSource.h = 72;

    SDL_Rect hotbarHighlightRect;

    hotbarHighlightRect.w = 72;
    hotbarHighlightRect.h = 72;

    hotbarHighlightRect.x = hotbarRect.x + 36;

    hotbarHighlightRect.y = hotbarRect.y + 32;

    SDL_RenderCopy(
        renderer,
        hotbarHighlightTexture,
        &hotbarHighlightSource,
        &hotbarHighlightRect
    );

    SDL_Texture* playerDownTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerDownSurface
        );

    if (playerDownTexture == nullptr)
    {
        std::cout << "Texture creation failed: "
            << SDL_GetError()
            << std::endl;
    }
    else
    {
        std::cout << "Player texture created successfully!"
            << std::endl;
    }

    SDL_FreeSurface(playerDownSurface);

    SDL_Surface* playerDownAxeSurface =
        IMG_Load(
            "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/DownAxe-Sheet.png"
        );

    SDL_Texture* playerDownAxeTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerDownAxeSurface
        );

    SDL_FreeSurface(playerDownAxeSurface);

    SDL_Surface* axeHitDownSurface =
        IMG_Load(
            "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/AxeHitDown-Sheet.png"
        );

    SDL_Texture* axeHitDownTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            axeHitDownSurface
        );

    SDL_FreeSurface(axeHitDownSurface);

    SDL_Surface* axeHitUpSurface =
        IMG_Load(
            "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/AxeHitUp-Sheet.png"
        );

    SDL_Texture* axeHitUpTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            axeHitUpSurface
        );

    SDL_FreeSurface(axeHitUpSurface);

    SDL_Surface* axeHitLeftSurface =
        IMG_Load(
            "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/AxeHitLeft-Sheet.png"
        );

    SDL_Texture* axeHitLeftTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            axeHitLeftSurface
        );

    SDL_FreeSurface(axeHitLeftSurface);

    SDL_Surface* axeHitRightSurface =
        IMG_Load(
            "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/AxeHitRight-Sheet.png"
        );

    SDL_Texture* axeHitRightTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            axeHitRightSurface
        );

    SDL_FreeSurface(axeHitRightSurface);

    
    SDL_Surface* playerUpLanternSurface =
        IMG_Load(
            "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/UpLantern.png"
        );

    SDL_Texture* playerUpLanternTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerUpLanternSurface
        );

    SDL_FreeSurface(playerUpLanternSurface);

    SDL_Surface* playerUpSurface =
        IMG_Load("C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/UpV1-Sheet.png");

    SDL_Texture* playerUpTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerUpSurface
        );

    SDL_FreeSurface(playerUpSurface);

    SDL_Surface* playerUpAxeSurface =
        IMG_Load(
            "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/UpAxe-Sheet.png"
        );

    SDL_Texture* playerUpAxeTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerUpAxeSurface
        );

    SDL_FreeSurface(playerUpAxeSurface);

    SDL_Surface* playerLeftLanternSurface =
        IMG_Load(
            "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/LeftLantern.png"
        );

    SDL_Texture* playerLeftLanternTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerLeftLanternSurface
        );

    SDL_FreeSurface(playerLeftLanternSurface);

    SDL_Surface* playerLeftSurface =
        IMG_Load("C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/LeftV1-Sheet.png");

    SDL_Texture* playerLeftTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerLeftSurface
        );

    SDL_FreeSurface(playerLeftSurface);

    SDL_Surface* playerLeftAxeSurface =
        IMG_Load(
            "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/LeftAxe-Sheet.png"
        );

    SDL_Texture* playerLeftAxeTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerLeftAxeSurface
        );

    SDL_FreeSurface(playerLeftAxeSurface);

    SDL_Surface* playerRightLanternSurface =
        IMG_Load(
            "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/RightLantern-Sheet.png"
        );

    SDL_Texture* playerRightLanternTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerRightLanternSurface
        );

    SDL_FreeSurface(playerRightLanternSurface);

    SDL_Surface* playerRightSurface =
        IMG_Load("C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/RightV1-Sheet.png");

    SDL_Texture* playerRightTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerRightSurface
        );

    SDL_FreeSurface(playerRightSurface);

    SDL_Surface* playerRightAxeSurface =
        IMG_Load(
            "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/RightAxe-Sheet.png"
        );

    SDL_Texture* playerRightAxeTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerRightAxeSurface
        );

    SDL_FreeSurface(playerRightAxeSurface);

    SDL_Texture* currentPlayerTexture = playerDownTexture;

    if (renderer == nullptr)
    {
        std::cout << "Renderer failed to start: "
            << SDL_GetError()
            << std::endl;

        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }

    //TTF_Font* font creates a variable that will hold font
    TTF_Font* font = TTF_OpenFont(
        "C:/Windows/Fonts/arial.ttf",
        36
    );

    TTF_Font* titleFont = TTF_OpenFont(
        "C:/Windows/Fonts/arial.ttf",
        72
    );

    if (font == nullptr)
    {
        std::cout << "Font failed to load: "
            << TTF_GetError()
            << std::endl;
    }

    SDL_Rect startButton;

    startButton.w = 300;
    startButton.h = 80;

    startButton.x = (1280 - startButton.w) / 2;
    startButton.y = (720 - startButton.h) / 2;

    SDL_Rect dayClockSourceRect;

    dayClockSourceRect.x = 21;
    dayClockSourceRect.y = 0;
    dayClockSourceRect.w = 21;
    dayClockSourceRect.h = 22;

    SDL_Rect dayClockRect;

    dayClockRect.w = 84;
    dayClockRect.h = 88;

    dayClockRect.x = 1280 - dayClockRect.w - 20;
    dayClockRect.y = 20;

    SDL_Rect heartSourceRect;

    heartSourceRect.x = 0;
    heartSourceRect.y = 0;
    heartSourceRect.w = 59;
    heartSourceRect.h = 10;

    int playerHealth = 5;
    const int maxPlayerHealth = 5;

    Uint32 lastBatDamageTime = 0;
    const Uint32 batDamageCooldown = 1000;

    SDL_Rect heartRect;

    heartRect.w = 236;
    heartRect.h = 40;

    heartRect.x =
        dayClockRect.x - heartRect.w - 12;

    heartRect.y =
        dayClockRect.y;

    SDL_Rect flameSourceRect;

    flameSourceRect.x = 0;
    flameSourceRect.y = 0;
    flameSourceRect.w = 59;
    flameSourceRect.h = 10;

    int flameAmmo = 5;
    const int maxFlameAmmo = 5;

    Uint32 lastFlameRechargeTime = SDL_GetTicks();
    const Uint32 flameRechargeDelay = 2000;

    SDL_Rect flameRect;

    flameRect.w = 236;
    flameRect.h = 40;

    flameRect.x = heartRect.x;

    flameRect.y =
        heartRect.y + heartRect.h + 8;

    SDL_Rect fireballSourceRect;

    fireballSourceRect.x = 0;
    fireballSourceRect.y = 0;
    fireballSourceRect.w = 32;
    fireballSourceRect.h = 32;

    SDL_Rect fireballRect;

    fireballRect.w = 128;
    fireballRect.h = 128;

    float fireballX = 0.0f;
    float fireballY = 0.0f;

    float fireballVelocityX = 0.0f;
    float fireballVelocityY = 0.0f;

    float fireballSpeed =6.0f;

    bool fireballActive = false;

    int fireballFrame = 0;

    Uint32 lastFireballFrameTime = SDL_GetTicks();
    const Uint32 fireballFrameDelay = 100;
    
    // This selects which 32x32 frame of the sprite sheet to show
    SDL_Rect playerSourceRect;

    playerSourceRect.x = 0;
    playerSourceRect.y = 0;
    playerSourceRect.w = 32;
    playerSourceRect.h = 32;

    SDL_Rect playerCollisionRect;

    playerCollisionRect.w = 44;
    playerCollisionRect.h = 44;


    // This controls WHERE and HOW LARGE the player appears on screen
    SDL_Rect player;

    player.w = 128;
    player.h = 128;


    // Smooth player position
    float playerX = 615.0f;
    float playerY = 335.0f;

    float cameraX = 0.0f;
    float cameraY = 0.0f;

    float nightAlpha = 0.0f;
    bool gettingDarker = true;

    SDL_Rect batSourceRect;

    batSourceRect.x = 0;
    batSourceRect.y = 0;
    batSourceRect.w = 26;
    batSourceRect.h = 26;

    SDL_Rect batRect;

    batRect.w = 104;
    batRect.h = 104;

    float batX = 0.0f;
    float batY = 0.0f;

    float batSpeed = 1.5f;

    bool batActive = false;
    bool batFlyingAway = false;

    int batHealth = 2;
    const int maxBatHealth = 2;

    int batFrame = 0;
    int batDirection = 0;

    Uint32 lastBatFrameTime = SDL_GetTicks();
    const Uint32 batFrameDelay = 120;

    SDL_Texture* currentBatTexture = batDownTexture;


    // Movement speed
    float playerSpeed = 2.5f;

    bool isMoving = false;

    int playerDirection = 0;


    // Put the float position into the SDL rectangle
    player.x = static_cast<int>(playerX);
    player.y = static_cast<int>(playerY);

    cameraX = playerX + (player.w / 2) - 640;
    cameraY = playerY + (player.h / 2) - 360;

    playerCollisionRect.x =
        player.x + (player.w - playerCollisionRect.w) / 2;

    playerCollisionRect.y =
        player.y + player.h - playerCollisionRect.h;

    int currentFrame = 0;
    int totalFrames = 8;

    SDL_Texture* lastPlayerTexture = currentPlayerTexture;

    Uint32 lastFrameTime = SDL_GetTicks();
    const Uint32 frameDelay = 120;

    Uint32 lastTreeFallTime = SDL_GetTicks();
    const Uint32 treeFallFrameDelay = 120;

    //SDL_Color text color creates the text color
    SDL_Color textColor = { 255, 255, 255, 255 };

    SDL_Surface* textSurface = TTF_RenderText_Solid(
        font,
        "START",
        textColor
    );

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
        renderer,
        textSurface
    );

    SDL_Surface* titleSurface = TTF_RenderText_Solid(
        titleFont,
        "Lanthorn",
        textColor
    );

    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(
        renderer,
        titleSurface
    );

    SDL_Rect titleRect;

    titleRect.w = titleSurface->w;
    titleRect.h = titleSurface->h;

    titleRect.x = startButton.x + (startButton.w - titleRect.w) / 2;
    titleRect.y = startButton.y - titleRect.h - 40;

    SDL_FreeSurface(titleSurface);

    SDL_Rect textRect;

    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    textRect.x = startButton.x + (startButton.w - textRect.w) / 2;
    textRect.y = startButton.y + (startButton.h - textRect.h) / 2;

    SDL_FreeSurface(textSurface);

    bool running = true;
    bool onTitleScreen = true;
    bool isFullscreen = true;

    int selectedSlot = 0;

    int lanternSlot = 0;
    bool movingLantern = false;

    int pickaxeSlot = 1;
    bool movingPickaxe = false;


    int axeSlot = 2;
    bool movingAxe = false;

    bool axeSwinging = false;

    int treeHitThisSwing = -1;

    SDL_Event event;

    while (running)
    {
        isMoving = false;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_SetWindowFullscreen(window, 0);

                    SDL_SetWindowSize(
                        window,
                        1280,
                        720
                    );

                    SDL_SetWindowPosition(
                        window,
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED
                    );

                    isFullscreen = false;
                }
            }


            // YOUR MOUSE / HOTBAR CODE
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // START BUTTON
                if (
                    mouseX >= startButton.x &&
                    mouseX <= startButton.x + startButton.w &&
                    mouseY >= startButton.y &&
                    mouseY <= startButton.y + startButton.h
                    )
                {
                    onTitleScreen = false;
                }

                // HOTBAR
                if (!onTitleScreen)
                {
                    
                    if (
                        mouseX >= hotbarRect.x &&
                        mouseX <= hotbarRect.x + hotbarRect.w &&
                        mouseY >= hotbarRect.y &&
                        mouseY <= hotbarRect.y + hotbarRect.h
                        )
                    {
                        selectedSlot = (mouseX - hotbarRect.x) / 72;

                        if (selectedSlot > 8)
                        {
                            selectedSlot = 8;
                        }

                        // Lantern is already being moved
                        if (movingLantern)
                        {
                            int oldLanternSlot = lanternSlot;

                            if (selectedSlot == pickaxeSlot)
                            {
                                lanternSlot = pickaxeSlot;
                                pickaxeSlot = oldLanternSlot;
                            }
                            else if (selectedSlot == axeSlot)
                            {
                                lanternSlot = axeSlot;
                                axeSlot = oldLanternSlot;
                            }
                            else
                            {
                                lanternSlot = selectedSlot;
                            }

                            movingLantern = false;
                        }

                        // Pickaxe is already being moved
                        else if (movingPickaxe)
                        {
                            int oldPickaxeSlot = pickaxeSlot;

                            if (selectedSlot == lanternSlot)
                            {
                                pickaxeSlot = lanternSlot;
                                lanternSlot = oldPickaxeSlot;
                            }
                            else if (selectedSlot == axeSlot)
                            {
                                pickaxeSlot = axeSlot;
                                axeSlot = oldPickaxeSlot;
                            }
                            else
                            {
                                pickaxeSlot = selectedSlot;
                            }

                            movingPickaxe = false;
                        }

                        // Axe is already being moved
                        else if (movingAxe)
                        {
                            int oldAxeSlot = axeSlot;

                            if (selectedSlot == lanternSlot)
                            {
                                axeSlot = lanternSlot;
                                lanternSlot = oldAxeSlot;
                            }
                            else if (selectedSlot == pickaxeSlot)
                            {
                                axeSlot = pickaxeSlot;
                                pickaxeSlot = oldAxeSlot;
                            }
                            else
                            {
                                axeSlot = selectedSlot;
                            }

                            movingAxe = false;
                        }

                        // Nothing is currently being moved
                        else
                        {
                            // Only pick up an item when it is DOUBLE CLICKED
                            if (event.button.clicks == 2)
                            {
                                if (selectedSlot == lanternSlot)
                                {
                                    movingLantern = true;
                                }
                                else if (selectedSlot == pickaxeSlot)
                                {
                                    movingPickaxe = true;
                                }
                                else if (selectedSlot == axeSlot)
                                {
                                    movingAxe = true;
                                }
                            }
                        }
                    }
                }
            }
        

            // ATTACK WITH LEFT MOUSE BUTTON
            if (
                event.type == SDL_MOUSEBUTTONDOWN &&
                event.button.button == SDL_BUTTON_LEFT &&
                !axeSwinging &&
                !fireballActive
                )
            {

                if (
                    selectedSlot == lanternSlot &&
                    flameAmmo > 0
                    )
                {
                    float mouseX =
                        static_cast<float>(event.button.x);

                    float mouseY =
                        static_cast<float>(event.button.y);

                    float playerScreenX =
                        player.x - cameraX +
                        (player.w / 2.0f);

                    float playerScreenY =
                        player.y - cameraY +
                        (player.h / 2.0f);

                    float directionX =
                        mouseX - playerScreenX;

                    float directionY =
                        mouseY - playerScreenY;

                    float length =
                        SDL_sqrtf(
                            directionX * directionX +
                            directionY * directionY
                        );

                    if (length > 0.0f)
                    {
                        directionX /= length;
                        directionY /= length;

                        fireballX =
                            playerX +
                            (player.w / 2) -
                            (fireballRect.w / 2);

                        fireballY =
                            playerY +
                            (player.h / 2) -
                            (fireballRect.h / 2);

                        fireballVelocityX =
                            directionX * fireballSpeed;

                        fireballVelocityY =
                            directionY * fireballSpeed;

                        fireballFrame = 0;
                        fireballSourceRect.x = 0;

                        lastFireballFrameTime =
                            SDL_GetTicks();

                        fireballActive = true;

                        flameAmmo--;

                        flameSourceRect.x =
                            (maxFlameAmmo - flameAmmo) * 59;

                        lastFlameRechargeTime =
                            SDL_GetTicks();
                    }
                }
                else if (selectedSlot == axeSlot)
                {
                    axeSwinging = true;

                    if (playerDirection == 0)
                    {
                        currentPlayerTexture = axeHitDownTexture;
                    }
                    else if (playerDirection == 1)
                    {
                        currentPlayerTexture = axeHitUpTexture;
                    }
                    else if (playerDirection == 2)
                    {
                        currentPlayerTexture = axeHitLeftTexture;
                    }
                    else if (playerDirection == 3)
                    {
                        currentPlayerTexture = axeHitRightTexture;
                    }

                    if (playerDirection == 2)
{
    SDL_Rect axeHitRect;

    axeHitRect.w = 60;
    axeHitRect.h = 68;

    axeHitRect.x =
        playerCollisionRect.x - axeHitRect.w;

    axeHitRect.y =
        playerCollisionRect.y - 26;

    for (int i = 0; i < TREE_COUNT; i++)
    {
       

        if (
            !treeFalling[i] &&
            !treeFallen[i])
        {
            int playerCenterX =
                playerCollisionRect.x +
                playerCollisionRect.w / 2;

            int treeCenterX =
                treeCollisionRects[i].x +
                treeCollisionRects[i].w / 2;

            // Player must be on RIGHT side of tree
            if (
                playerCenterX > treeCenterX &&
                CheckCollision(
                    axeHitRect,
                    treeCollisionRects[i]
                )
            )
            {
                treeHitThisSwing = i;
                if (treeFlipped[i])
                {
                    treeFallDirection[i] = 0;
                }
                else
                {
                    treeFallDirection[i] = 1;
                }
                treeRandomFall[i] = false;

                break;
            }
        }
    }
}

                    currentFrame = 0;
                    totalFrames = 7;
                    lastFrameTime = SDL_GetTicks();
                    // CHECK IF THE AXE HITS TREE 1 FROM THE LEFT SIDE
                    if (playerDirection == 3)
                    {
                        SDL_Rect axeHitRect;

                        axeHitRect.w = 60;
                        axeHitRect.h = 68;

                        axeHitRect.x =
                            playerCollisionRect.x + playerCollisionRect.w;

                        axeHitRect.y =
                            playerCollisionRect.y - 26;

                        for (int i = 0; i < TREE_COUNT; i++)
                        {
                            // treeTypes[i] == 0 means Tree 1
                            if (!treeFalling[i] && !treeFallen[i])
                            {
                                int playerCenterX =
                                    playerCollisionRect.x +
                                    playerCollisionRect.w / 2;

                                int treeCenterX =
                                    treeCollisionRects[i].x +
                                    treeCollisionRects[i].w / 2;

                                // Player must be on the LEFT side of the tree
                                if (
                                    playerCenterX < treeCenterX &&
                                    CheckCollision(
                                        axeHitRect,
                                        treeCollisionRects[i]
                                    )
                                    )
                                {
                                    treeHitThisSwing = i;
                                    if (treeFlipped[i])
                                    {
                                        treeFallDirection[i] = 1;
                                    }
                                    else
                                    {
                                        treeFallDirection[i] = 0;
                                    }
                                    treeRandomFall[i] = false;
                                    // Only hit one tree per swing
                                    break;
                                }
                     
                            }
                        }
                    }
                    // PLAYER IS ABOVE TREE, FACING DOWN
                    if (playerDirection == 0)
                    {
                        SDL_Rect axeHitRect;

                        axeHitRect.w = 60;
                        axeHitRect.h = 60;

                        axeHitRect.x =
                            playerCollisionRect.x +
                            (playerCollisionRect.w - axeHitRect.w) / 2;

                        axeHitRect.y =
                            playerCollisionRect.y +
                            playerCollisionRect.h;

                        for (int i = 0; i < TREE_COUNT; i++)
                        {
                            if (
                                !treeFalling[i] &&
                                !treeFallen[i])
                            {
                                if (CheckCollision(
                                    axeHitRect,
                                    treeCollisionRects[i]
                                ))
                                {
                                    treeHitThisSwing = i;
                                    treeRandomFall[i] = true;

                                    break;
                                }
                            }
                        }
                    }

                    // PLAYER IS BELOW TREE, FACING UP
                    if (playerDirection == 1)
                    {
                        SDL_Rect axeHitRect;

                        axeHitRect.w = 60;
                        axeHitRect.h = 60;

                        axeHitRect.x =
                            playerCollisionRect.x +
                            (playerCollisionRect.w - axeHitRect.w) / 2;

                        axeHitRect.y =
                            playerCollisionRect.y -
                            axeHitRect.h;

                        for (int i = 0; i < TREE_COUNT; i++)
                        {
                            if (
                                !treeFalling[i] &&
                                !treeFallen[i])
                            {
                                if (CheckCollision(
                                    axeHitRect,
                                    treeCollisionRects[i]
                                ))
                                {
                                    treeHitThisSwing = i;
                                    treeRandomFall[i] = true;

                                    break;
                                }
                            }
                        }
                    }
                }
            }

          

            // F11 FULLSCREEN
            if (
                event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_F11 &&
                event.key.repeat == 0
                )
            {
                isFullscreen = !isFullscreen;

                if (isFullscreen)
                {
                    SDL_SetWindowFullscreen(
                        window,
                        SDL_WINDOW_FULLSCREEN_DESKTOP
                    );
                }
                else
                {
                    SDL_SetWindowFullscreen(window, 0);

                    SDL_SetWindowSize(
                        window,
                        1280,
                        720
                    );

                    SDL_SetWindowPosition(
                        window,
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED
                    );
                }
            }
        }

        const Uint8* keyboardState =
            SDL_GetKeyboardState(nullptr);
        if (!onTitleScreen && !axeSwinging)
        {
            SDL_Rect nextPlayer = player;
            SDL_Rect nextPlayerCollisionRect = playerCollisionRect;

            bool blockedByTree = false;
            if (keyboardState[SDL_SCANCODE_W])
            {
                nextPlayer = player;
                nextPlayer.y = static_cast<int>(playerY - playerSpeed);

                nextPlayerCollisionRect = playerCollisionRect;

                nextPlayerCollisionRect.x =
                    nextPlayer.x + (nextPlayer.w - nextPlayerCollisionRect.w) / 2;

                nextPlayerCollisionRect.y =
                    nextPlayer.y + nextPlayer.h - nextPlayerCollisionRect.h;

                blockedByTree = false;

                for (int i = 0; i < TREE_COUNT; i++)
                {
                    SDL_Rect currentTreeCollision;

                    if (treeFallen[i])
                    {
                        currentTreeCollision = stumpCollisionRects[i];
                    }
                    else
                    {
                        currentTreeCollision = treeCollisionRects[i];
                    }

                    if (CheckCollision(
                        nextPlayerCollisionRect,
                        currentTreeCollision
                    ))
                    {
                        blockedByTree = true;
                    }
                }

                if (!blockedByTree)
                {
                    playerY -= playerSpeed;
                }

                playerDirection = 1;

                if (selectedSlot == lanternSlot)
                {
                    currentPlayerTexture = playerUpLanternTexture;
                }
                else if (selectedSlot == axeSlot)
                {
                    currentPlayerTexture = playerUpAxeTexture;
                }
                else
                {
                    currentPlayerTexture = playerUpTexture;
                }

                totalFrames = 2;
                isMoving = true;
            }

            if (keyboardState[SDL_SCANCODE_S])
            {
                nextPlayer = player;
                nextPlayer.y = static_cast<int>(playerY + playerSpeed);

                nextPlayerCollisionRect = playerCollisionRect;

                nextPlayerCollisionRect.x =
                    nextPlayer.x + (nextPlayer.w - nextPlayerCollisionRect.w) / 2;

                nextPlayerCollisionRect.y =
                    nextPlayer.y + nextPlayer.h - nextPlayerCollisionRect.h;

                blockedByTree = false;
                for (int i = 0; i < TREE_COUNT; i++)
                {
                    SDL_Rect currentTreeCollision;

                    if (treeFallen[i])
                    {
                        currentTreeCollision = stumpCollisionRects[i];
                    }
                    else
                    {
                        currentTreeCollision = treeCollisionRects[i];
                    }

                    if (CheckCollision(
                        nextPlayerCollisionRect,
                        currentTreeCollision
                    ))
                    {
                        blockedByTree = true;
                    }
                }

                if (!blockedByTree)
                {
                    playerY += playerSpeed;
                }

                playerDirection = 0;

                if (selectedSlot == lanternSlot)
                {
                    currentPlayerTexture = playerDownLanternTexture;
                }
                else if (selectedSlot == axeSlot)
                {
                    currentPlayerTexture = playerDownAxeTexture;
                }
                else
                {
                    currentPlayerTexture = playerDownTexture;
                }

                totalFrames = 8;
                isMoving = true;
            }

            if (keyboardState[SDL_SCANCODE_A])
            {
                nextPlayer = player;
                nextPlayer.x = static_cast<int>(playerX - playerSpeed);

                nextPlayerCollisionRect = playerCollisionRect;

                nextPlayerCollisionRect.x =
                    nextPlayer.x + (nextPlayer.w - nextPlayerCollisionRect.w) / 2;

                nextPlayerCollisionRect.y =
                    nextPlayer.y + nextPlayer.h - nextPlayerCollisionRect.h;

                blockedByTree = false;

                for (int i = 0; i < TREE_COUNT; i++)
                {
                    SDL_Rect currentTreeCollision;

                    if (treeFallen[i])
                    {
                        currentTreeCollision = stumpCollisionRects[i];
                    }
                    else
                    {
                        currentTreeCollision = treeCollisionRects[i];
                    }

                    if (CheckCollision(
                        nextPlayerCollisionRect,
                        currentTreeCollision
                    ))
                    {
                        blockedByTree = true;
                    }
                }

                if (!blockedByTree)
                {
                    playerX -= playerSpeed;
             
                }
                playerDirection = 2;

                if (selectedSlot == lanternSlot)
                {
                    currentPlayerTexture = playerLeftLanternTexture;
                }
                else if (selectedSlot == axeSlot)
                {
                    currentPlayerTexture = playerLeftAxeTexture;
                }
                else
                {
                    currentPlayerTexture = playerLeftTexture;
                }

                totalFrames = 6;
                isMoving = true;
            }
            if (keyboardState[SDL_SCANCODE_D])
            {
                nextPlayer = player;
                nextPlayer.x = static_cast<int>(playerX + playerSpeed);

                nextPlayerCollisionRect = playerCollisionRect;

                nextPlayerCollisionRect.x =
                    nextPlayer.x + (nextPlayer.w - nextPlayerCollisionRect.w) / 2;

                nextPlayerCollisionRect.y =
                    nextPlayer.y + nextPlayer.h - nextPlayerCollisionRect.h;

                blockedByTree = false;
                for (int i = 0; i < TREE_COUNT; i++)
                {
                    SDL_Rect currentTreeCollision;

                    if (treeFallen[i])
                    {
                        currentTreeCollision = stumpCollisionRects[i];
                    }
                    else
                    {
                        currentTreeCollision = treeCollisionRects[i];
                    }

                    if (CheckCollision(
                        nextPlayerCollisionRect,
                        currentTreeCollision
                    ))
                    {
                        blockedByTree = true;
                    }
                }

                if (!blockedByTree)
                {
                    playerX += playerSpeed;
                }
                playerDirection = 3;

                if (selectedSlot == lanternSlot)
                {
                    currentPlayerTexture = playerRightLanternTexture;
                }
                else if (selectedSlot == axeSlot)
                {
                    currentPlayerTexture = playerRightAxeTexture;
                }
                else
                {
                    currentPlayerTexture = playerRightTexture;
                }

                totalFrames = 6;
                isMoving = true;
            }
            player.x = static_cast<int>(playerX);
            player.y = static_cast<int>(playerY);

            cameraX = playerX + (player.w / 2) - 640;
            cameraY = playerY + (player.h / 2) - 360;

            // Keep the 40 x 16 collision box at the player's feet
            playerCollisionRect.x =
                player.x + (player.w - playerCollisionRect.w) / 2;

            playerCollisionRect.y =
                player.y + player.h - playerCollisionRect.h;
        }
        if (!isMoving && !axeSwinging)
        {
            // LANTERN IS HIGHLIGHTED
            if (selectedSlot == lanternSlot)
            {
                if (currentPlayerTexture == playerDownTexture ||
                    currentPlayerTexture == playerDownAxeTexture)
                {
                    currentPlayerTexture = playerDownLanternTexture;
                }
                else if (currentPlayerTexture == playerUpTexture ||
                    currentPlayerTexture == playerUpAxeTexture)
                {
                    currentPlayerTexture = playerUpLanternTexture;
                }
                else if (currentPlayerTexture == playerLeftTexture ||
                    currentPlayerTexture == playerLeftAxeTexture)
                {
                    currentPlayerTexture = playerLeftLanternTexture;
                }
                else if (currentPlayerTexture == playerRightTexture ||
                    currentPlayerTexture == playerRightAxeTexture)
                {
                    currentPlayerTexture = playerRightLanternTexture;
                }
            }

            // AXE IS HIGHLIGHTED
            else if (selectedSlot == axeSlot)
            {
                if (currentPlayerTexture == playerDownTexture ||
                    currentPlayerTexture == playerDownLanternTexture)
                {
                    currentPlayerTexture = playerDownAxeTexture;
                }
                else if (currentPlayerTexture == playerUpTexture ||
                    currentPlayerTexture == playerUpLanternTexture)
                {
                    currentPlayerTexture = playerUpAxeTexture;
                }
                else if (currentPlayerTexture == playerLeftTexture ||
                    currentPlayerTexture == playerLeftLanternTexture)
                {
                    currentPlayerTexture = playerLeftAxeTexture;
                }
                else if (currentPlayerTexture == playerRightTexture ||
                    currentPlayerTexture == playerRightLanternTexture)
                {
                    currentPlayerTexture = playerRightAxeTexture;
                }
            }

            // NEITHER LANTERN NOR AXE IS HIGHLIGHTED
            else
            {
                if (currentPlayerTexture == playerDownLanternTexture ||
                    currentPlayerTexture == playerDownAxeTexture)
                {
                    currentPlayerTexture = playerDownTexture;
                }
                else if (currentPlayerTexture == playerUpLanternTexture ||
                    currentPlayerTexture == playerUpAxeTexture)
                {
                    currentPlayerTexture = playerUpTexture;
                }
                else if (currentPlayerTexture == playerLeftLanternTexture ||
                    currentPlayerTexture == playerLeftAxeTexture)
                {
                    currentPlayerTexture = playerLeftTexture;
                }
                else if (currentPlayerTexture == playerRightLanternTexture ||
                    currentPlayerTexture == playerRightAxeTexture)
                {
                    currentPlayerTexture = playerRightTexture;
                }
            }
        }


        // YOUR EXISTING CODE CONTINUES HERE

        
        if (currentPlayerTexture != lastPlayerTexture)
        {
            currentFrame = 0;
            lastFrameTime = SDL_GetTicks();
            lastPlayerTexture = currentPlayerTexture;
        }
        Uint32 currentTime = SDL_GetTicks();

        if (
            flameAmmo < maxFlameAmmo &&
            currentTime - lastFlameRechargeTime >=
            flameRechargeDelay
            )
        {
            flameAmmo++;

            flameSourceRect.x =
                (maxFlameAmmo - flameAmmo) * 59;

            lastFlameRechargeTime =
                currentTime;
        }

        if (gettingDarker)
        {
            nightAlpha += 0.05f;

            if (nightAlpha >= 180.0f)
            {
                nightAlpha = 180.0f;
                gettingDarker = false;
            }
        }
        else
        {
            nightAlpha -= 0.05f;

            if (nightAlpha <= 0.0f)
            {
                nightAlpha = 0.0f;
                gettingDarker = true;
            }
        }

        if (nightAlpha >= 120.0f && !batActive)
        {
            batActive = true;
            batFlyingAway = false;

            batHealth = maxBatHealth;

            batX = playerX + 700.0f;
            batY = playerY;

            batFrame = 0;
            batDirection = 2;

            currentBatTexture = batLeftTexture;

            lastBatFrameTime = currentTime;
        }

        if (batActive)
        {
            if (nightAlpha < 40.0f)
            {
                batFlyingAway = true;
            }

            if (!batFlyingAway)
            {
                float batDX = playerX - batX;
                float batDY = playerY - batY;

                float absBatDX =
                    batDX < 0.0f ? -batDX : batDX;

                float absBatDY =
                    batDY < 0.0f ? -batDY : batDY;

                if (batDX < 0.0f)
                {
                    batX -= batSpeed;
                }
                else if (batDX > 0.0f)
                {
                    batX += batSpeed;
                }

                if (batDY < 0.0f)
                {
                    batY -= batSpeed;
                }
                else if (batDY > 0.0f)
                {
                    batY += batSpeed;
                }

                if (absBatDX > absBatDY)
                {
                    if (batDX < 0.0f)
                    {
                        currentBatTexture = batLeftTexture;
                        batDirection = 2;
                    }
                    else
                    {
                        currentBatTexture = batRightTexture;
                        batDirection = 3;
                    }
                }
                else
                {
                    if (batDY < 0.0f)
                    {
                        currentBatTexture = batUpTexture;
                        batDirection = 1;
                    }
                    else
                    {
                        currentBatTexture = batDownTexture;
                        batDirection = 0;
                    }
                }
            }
            else
            {
                batY -= batSpeed * 2.0f;

                currentBatTexture = batUpTexture;
                batDirection = 1;

                if (batY < playerY - 900.0f)
                {
                    batActive = false;
                    batFlyingAway = false;
                }
            }
        }

        if (batActive &&
            currentTime - lastBatFrameTime >= batFrameDelay)
        {
            batFrame++;

            if (batFrame >= 4)
            {
                batFrame = 0;
            }

            batSourceRect.x = batFrame * 26;
            batSourceRect.y = 0;

            lastBatFrameTime = currentTime;
        }

        if (batActive && !batFlyingAway)
        {
            SDL_Rect batCollisionRect;

            batCollisionRect.w = 40;
            batCollisionRect.h = 40;

            batCollisionRect.x =
                static_cast<int>(batX) +
                (104 - batCollisionRect.w) / 2;

            batCollisionRect.y =
                static_cast<int>(batY) +
                (104 - batCollisionRect.h) / 2;

            if (
                CheckCollision(
                    batCollisionRect,
                    playerCollisionRect
                ) &&
                currentTime - lastBatDamageTime >=
                batDamageCooldown
                )
            {
                if (playerHealth > 0)
                {
                    playerHealth--;

                    heartSourceRect.x =
                        (maxPlayerHealth - playerHealth) * 59;
                }

                lastBatDamageTime = currentTime;
            }
        }

        int dayClockFrame = 1;

        if (gettingDarker)
        {
            float dayProgress =
                nightAlpha / 180.0f;

            dayClockFrame =
                1 + static_cast<int>(
                    dayProgress * 8.0f + 0.5f
                    );
        }
        else
        {
            float nightProgress =
                (180.0f - nightAlpha) / 180.0f;

            int lighteningStep =
                static_cast<int>(
                    nightProgress * 8.0f + 0.5f
                    );

            dayClockFrame =
                (9 + lighteningStep) % 16;
        }

        dayClockSourceRect.x =
            dayClockFrame * 21;

        
        if (fireballActive)
        {
            fireballX += fireballVelocityX;
            fireballY += fireballVelocityY;

            fireballRect.x =
                static_cast<int>(fireballX - cameraX);

            fireballRect.y =
                static_cast<int>(fireballY - cameraY);

            SDL_Rect fireballCollisionRect;

            fireballCollisionRect.w = 20;
            fireballCollisionRect.h = 20;

            fireballCollisionRect.x =
                static_cast<int>(fireballX) + 52;

            fireballCollisionRect.y =
                static_cast<int>(fireballY) + 56;

            SDL_Rect batHitRect;

            batHitRect.w = 40;
            batHitRect.h = 40;

            batHitRect.x =
                static_cast<int>(batX) +
                (104 - batHitRect.w) / 2;

            batHitRect.y =
                static_cast<int>(batY) +
                (104 - batHitRect.h) / 2;

            if (
                batActive &&
                !batFlyingAway &&
                CheckCollision(
                    fireballCollisionRect,
                    batHitRect
                )
                )
            {
                batHealth--;

                fireballActive = false;

                if (batHealth <= 0)
                {
                    batActive = false;
                }
            }

            for (int i = 0; i < TREE_COUNT; i++)
            {
                if (treeFallen[i])
                {
                    continue;
                }

                if (CheckCollision(
                    fireballCollisionRect,
                    treeCollisionRects[i]
                ))
                {
                    fireballActive = false;
                    break;
                }
            }

            if (
                currentTime - lastFireballFrameTime >=
                fireballFrameDelay
                )
            {
                fireballFrame++;

                if (fireballFrame >= 4)
                {
                    fireballFrame = 0;
                }

                fireballSourceRect.x =
                    fireballFrame * 32;

                lastFireballFrameTime =
                    currentTime;
            }

            if (
                fireballRect.x < -64 ||
                fireballRect.x > 1344 ||
                fireballRect.y < -64 ||
                fireballRect.y > 784
                )
            {
                fireballActive = false;
            }
        }

        if (currentTime - lastTreeFallTime >= treeFallFrameDelay)
        {
            for (int i = 0; i < TREE_COUNT; i++)
            {
                if (treeFalling[i])
                {
                    treeFallFrame[i]++;

                    if (treeFallFrame[i] >= 9)
                    {
                        treeFallFrame[i] = 8;
                        treeFalling[i] = false;
                        treeFallen[i] = true;
                    }
                }
            }

            lastTreeFallTime = currentTime;
        }

        if (axeSwinging)
        {
            if (currentTime - lastFrameTime >= frameDelay)
            {
                currentFrame++;

                if (currentFrame >= 7)
                {
                    currentFrame = 0;
                    axeSwinging = false;

                    if (treeHitThisSwing != -1)
                    {
                        treeHits[treeHitThisSwing]++;

                        if (treeHits[treeHitThisSwing] >= 5)
                        {
                            if (treeRandomFall[treeHitThisSwing])
                            {
                                treeFallDirection[treeHitThisSwing] =
                                    std::rand() % 2;

                                if (treeFlipped[treeHitThisSwing])
                                {
                                    treeFallDirection[treeHitThisSwing] =
                                        1 - treeFallDirection[treeHitThisSwing];
                                }
                            }

                            treeFalling[treeHitThisSwing] = true;
                            treeFallFrame[treeHitThisSwing] = 0;
                        }

                        treeHitThisSwing = -1;
                    }
                }

                lastFrameTime = currentTime;
            }
        }
        else if (isMoving)
        {
            if (currentTime - lastFrameTime >= frameDelay)
            {
                currentFrame++;

                if (currentFrame >= totalFrames)
                {
                    currentFrame = 0;
                }

                lastFrameTime = currentTime;
            }
        }
        else
        {
            currentFrame = 0;
        }

        playerSourceRect.x = currentFrame * 32;

        // Check which keyboard keys are currently being held down.


        // TITLE SCREEN
        if (onTitleScreen)
        {
            SDL_SetRenderDrawColor(
                renderer,
                10,
                12,
                16,
                255
            );

            SDL_RenderClear(renderer);

            // Draw Lanthorn title.
            SDL_RenderCopy(
                renderer,
                titleTexture,
                nullptr,
                &titleRect
            );

            // Draw START button.
            SDL_SetRenderDrawColor(
                renderer,
                170,
                120,
                45,
                255
            );

            SDL_RenderFillRect(
                renderer,
                &startButton
            );

            // Draw START text.
            SDL_RenderCopy(
                renderer,
                textTexture,
                nullptr,
                &textRect
            );
        }

        // GAME SCREEN
        else
        {
            // Set background color.
            SDL_SetRenderDrawColor(
                renderer,
                20,
                20,
                20,
                255
            );

            // Clear the old frame.
            SDL_RenderClear(renderer);
            const int tileSize = 128;
            const int mapTiles = 100;
            const float mapCenter = 49.5f;
            const float mapRadius = 50.0f;
            const int mapOffsetX = 640 - (50 * tileSize);
            const int mapOffsetY = 360 - (50 * tileSize);

            for (int tileY = 0; tileY < mapTiles; tileY++)
            {
                for (int tileX = 0; tileX < mapTiles; tileX++)
                {
                    float dx = tileX - mapCenter;
                    float dy = tileY - mapCenter;

                    if ((dx * dx) + (dy * dy) <= mapRadius * mapRadius)
                    {
                        SDL_Rect grassTileRect;

                        grassTileRect.x =
                            mapOffsetX + tileX * tileSize - static_cast<int>(cameraX);

                        grassTileRect.y =
                            mapOffsetY + tileY * tileSize - static_cast<int>(cameraY);
                        grassTileRect.w = tileSize;
                        grassTileRect.h = tileSize;

                        SDL_RenderCopy(
                            renderer,
                            backgroundTexture,
                            nullptr,
                            &grassTileRect
                        );
                    }
                }
            }

            if (batActive)
            {
                batRect.x =
                    static_cast<int>(batX - cameraX);

                batRect.y =
                    static_cast<int>(batY - cameraY);

                SDL_RenderCopy(
                    renderer,
                    currentBatTexture,
                    &batSourceRect,
                    &batRect
                );
            }

            std::vector<int> sortedTrees;
            for (int i = 0; i < TREE_COUNT; i++)
            {
                int treeScreenX =
                    treeRects[i].x - static_cast<int>(cameraX);

                int treeScreenY =
                    treeRects[i].y - static_cast<int>(cameraY);

                if (
                    treeScreenX >= -420 &&
                    treeScreenX <= 1580 &&
                    treeScreenY >= -360 &&
                    treeScreenY <= 720
                    )
                {
                    sortedTrees.push_back(i);
                }
            }

            std::sort(
                sortedTrees.begin(),
                sortedTrees.end(),
                [&](int a, int b)
                {
                    int bottomA =
                        treeCollisionRects[a].y +
                        treeCollisionRects[a].h;

                    int bottomB =
                        treeCollisionRects[b].y +
                        treeCollisionRects[b].h;

                    return bottomA < bottomB;
                }
            );

            // FIRST TREE PASS
// Draw normal trees behind the player.
// Draw falling trees and stumps normally.
            for (int i : sortedTrees)
            {

                
            
                // FALLEN TREE = STUMP ONLY
                if (treeFallen[i])
                {
                    SDL_Rect stumpRect;

                    stumpRect.w = 140;
                    stumpRect.h = 356;

                    stumpRect.x = treeRects[i].x;
                    stumpRect.y = treeRects[i].y;

                    stumpRect.x -= static_cast<int>(cameraX);
                    stumpRect.y -= static_cast<int>(cameraY);

                    int playerBottom =
                        playerCollisionRect.y + playerCollisionRect.h;

                    int stumpBottom =
                        stumpCollisionRects[i].y + stumpCollisionRects[i].h;

                    bool playerOverlapsStumpX =
                        playerCollisionRect.x + playerCollisionRect.w >
                        stumpCollisionRects[i].x &&
                        playerCollisionRect.x <
                        stumpCollisionRects[i].x + stumpCollisionRects[i].w;

                    if (!playerOverlapsStumpX ||
                        playerBottom >= stumpBottom)
                    {
                        SDL_Texture* stumpTexture;

                        if (treeTypes[i] == 0)
                        {
                            stumpTexture = cypressStumpTexture;
                        }
                        else
                        {
                            stumpTexture = deadStumpTexture;
                        }

                        SDL_RenderCopyEx(
                            renderer,
                            stumpTexture,
                            nullptr,
                            &stumpRect,
                            0.0,
                            nullptr,
                            treeFlipped[i]
                            ? SDL_FLIP_HORIZONTAL
                            : SDL_FLIP_NONE
                       
                        );
                    }
                }

                // TREE IS CURRENTLY FALLING
           
                else if (
                    treeFalling[i] &&
                    playerCollisionRect.y + playerCollisionRect.h >=
                    treeCollisionRects[i].y + treeCollisionRects[i].h
                    )
                {
                    SDL_Rect treeFallSourceRect;

                    treeFallSourceRect.x = treeFallFrame[i] * 97;
                    treeFallSourceRect.y = 0;
                    treeFallSourceRect.w = 97;
                    treeFallSourceRect.h = 89;

                    SDL_Rect treeFallRect;

                    treeFallRect.w = 416;
                    treeFallRect.h = 356;

                    if (!treeFlipped[i])
                    {
                        if (treeFallDirection[i] == 0)
                        {
                            treeFallRect.x = treeRects[i].x;
                        }
                        else
                        {
                            treeFallRect.x =
                                treeRects[i].x - ((104 - 35) * 4);
                        }
                    }
                    else
                    {
                        if (treeFallDirection[i] == 0)
                        {
                            // Reversed falling-right:
                            // far-right edge stays aligned with tree
                            treeFallRect.x =
                                treeRects[i].x - ((104 - 35) * 4);
                        }
                        else
                        {
                            // Reversed falling-left:
                            // left edge stays aligned with tree
                            treeFallRect.x = treeRects[i].x;
                        }
                    }

                    treeFallRect.y = treeRects[i].y;

                    treeFallRect.x -= static_cast<int>(cameraX);
                    treeFallRect.y -= static_cast<int>(cameraY);

                    SDL_Texture* fallingTexture;

                    if (treeTypes[i] == 0)
                    {
                        if (treeFallDirection[i] == 0)
                        {
                            fallingTexture = cypressRightTexture;
                        }
                        else
                        {
                            fallingTexture = cypressLeftTexture;
                        }
                    }
                    else
                    {
                        if (treeFallDirection[i] == 0)
                        {
                            fallingTexture = deadRightTexture;
                        }
                        else
                        {
                            fallingTexture = deadLeftTexture;
                        }
                    }

                    SDL_RenderCopyEx(
                        renderer,
                        fallingTexture,
                        &treeFallSourceRect,
                        &treeFallRect,
                        0.0,
                        nullptr,
                        treeFlipped[i]
                        ? SDL_FLIP_HORIZONTAL
                        : SDL_FLIP_NONE
                    );
                }

                // TREE IS STILL STANDING
                else if (!treeFalling[i])
                {
                    bool playerUnderTree =
                        CheckCollision(player, treeRects[i]) &&
                        !CheckCollision(player, treeCollisionRects[i]);

                    // If player is NOT underneath it,
                    // draw the full tree now.
                    if (!playerUnderTree)
                    {
                        SDL_Texture* treeTexture;

                        if (treeTypes[i] == 0)
                        {
                            treeTexture = cypressTexture;
                        }
                        else
                        {
                            treeTexture = deadTexture;
                        }

                        SDL_SetTextureAlphaMod(treeTexture, 255);
                        SDL_Rect treeRenderRect = treeRects[i];

                        treeRenderRect.x -= static_cast<int>(cameraX);
                        treeRenderRect.y -= static_cast<int>(cameraY);
                        SDL_RenderCopyEx(
                            renderer,
                            treeTexture,
                            nullptr,
                            &treeRenderRect,
                            0.0,
                            nullptr,
                            treeFlipped[i]
                            ? SDL_FLIP_HORIZONTAL
                            : SDL_FLIP_NONE
                       
                        );
                    }
                }
            }
            // Draw the player.
            SDL_Rect playerRenderRect = player;

            playerRenderRect.x = 640 - (player.w / 2);
            playerRenderRect.y = 360 - (player.h / 2);
            
            SDL_RenderCopy(
                renderer,
                currentPlayerTexture,
                &playerSourceRect,
                &playerRenderRect
            );

            // SECOND TREE PASS
            // Only standing trees can become transparent.

            for (int i : sortedTrees)
            {


                if (
                    treeFalling[i] &&
                    playerCollisionRect.y + playerCollisionRect.h <
                    treeCollisionRects[i].y + treeCollisionRects[i].h
                    )
                {
                    SDL_Rect treeFallSourceRect;

                    treeFallSourceRect.x = treeFallFrame[i] * 97;
                    treeFallSourceRect.y = 0;
                    treeFallSourceRect.w = 97;
                    treeFallSourceRect.h = 89;

                    SDL_Rect treeFallRect;

                    treeFallRect.w = 416;
                    treeFallRect.h = 356;

                    if (!treeFlipped[i])
                    {
                        if (treeFallDirection[i] == 0)
                        {
                            treeFallRect.x = treeRects[i].x;
                        }
                        else
                        {
                            treeFallRect.x =
                                treeRects[i].x - ((104 - 35) * 4);
                        }
                    }
                    else
                    {
                        if (treeFallDirection[i] == 0)
                        {
                            treeFallRect.x =
                                treeRects[i].x - ((104 - 35) * 4);
                        }
                        else
                        {
                            treeFallRect.x = treeRects[i].x;
                        }
                    }

                    treeFallRect.y = treeRects[i].y;
                    treeFallRect.x -= static_cast<int>(cameraX);
                    treeFallRect.y -= static_cast<int>(cameraY);
                    SDL_Texture* fallingTexture;

                    if (treeTypes[i] == 0)
                    {
                        if (treeFallDirection[i] == 0)
                        {
                            fallingTexture = cypressRightTexture;
                        }
                        else
                        {
                            fallingTexture = cypressLeftTexture;
                        }
                    }
                    else
                    {
                        if (treeFallDirection[i] == 0)
                        {
                            fallingTexture = deadRightTexture;
                        }
                        else
                        {
                            fallingTexture = deadLeftTexture;
                        }
                    }

                    SDL_RenderCopyEx(
                        renderer,
                        fallingTexture,
                        &treeFallSourceRect,
                        &treeFallRect,
                        0.0,
                        nullptr,
                        treeFlipped[i]
                        ? SDL_FLIP_HORIZONTAL
                        : SDL_FLIP_NONE
                    );
                }
                else if (treeFallen[i])
                {
                    int playerBottom =
                        playerCollisionRect.y + playerCollisionRect.h;

                    int stumpBottom =
                        stumpCollisionRects[i].y + stumpCollisionRects[i].h;

                    bool playerOverlapsStumpX =
                        playerCollisionRect.x + playerCollisionRect.w >
                        stumpCollisionRects[i].x &&
                        playerCollisionRect.x <
                        stumpCollisionRects[i].x + stumpCollisionRects[i].w;

                    if (playerOverlapsStumpX &&
                        playerBottom < stumpBottom)
                    {
                        SDL_Rect stumpRect;

                        stumpRect.w = 140;
                        stumpRect.h = 356;

                        stumpRect.x = treeRects[i].x;
                        stumpRect.y = treeRects[i].y;

                        stumpRect.x -= static_cast<int>(cameraX);
                        stumpRect.y -= static_cast<int>(cameraY);

                        SDL_Texture* stumpTexture;

                        if (treeTypes[i] == 0)
                        {
                            stumpTexture = cypressStumpTexture;
                        }
                        else
                        {
                            stumpTexture = deadStumpTexture;
                        }

                        SDL_RenderCopyEx(
                            renderer,
                            stumpTexture,
                            nullptr,
                            &stumpRect,
                            0.0,
                            nullptr,
                            treeFlipped[i]
                            ? SDL_FLIP_HORIZONTAL
                            : SDL_FLIP_NONE
                       
                        );
                    }
                }
                else if (!treeFalling[i] && !treeFallen[i])
                {
                    bool playerUnderTree =
                        CheckCollision(player, treeRects[i]) &&
                        !CheckCollision(player, treeCollisionRects[i]);

                    if (playerUnderTree)
                    {
                        SDL_Texture* treeTexture;

                        if (treeTypes[i] == 0)
                        {
                            treeTexture = cypressTexture;
                        }
                        else
                        {
                            treeTexture = deadTexture;
                        }

                        SDL_SetTextureAlphaMod(treeTexture, 128);

                        SDL_Rect treeRenderRect = treeRects[i];

                        treeRenderRect.x -= static_cast<int>(cameraX);
                        treeRenderRect.y -= static_cast<int>(cameraY);

                        SDL_RenderCopyEx(
                            renderer,
                            treeTexture,
                            nullptr,
                            &treeRenderRect,
                            0.0,
                            nullptr,
                            treeFlipped[i]
                            ? SDL_FLIP_HORIZONTAL
                            : SDL_FLIP_NONE
                        
                        );

                        SDL_SetTextureAlphaMod(treeTexture, 255);
                    }
                }
            }
            
            SDL_SetRenderTarget(
                renderer,
                darknessTexture
            );

            SDL_SetRenderDrawColor(
                renderer,
                0,
                0,
                0,
                0
            );

            SDL_RenderClear(renderer);

            bool lanternActive =
                currentPlayerTexture == playerDownLanternTexture ||
                currentPlayerTexture == playerUpLanternTexture ||
                currentPlayerTexture == playerLeftLanternTexture ||
                currentPlayerTexture == playerRightLanternTexture;

            SDL_SetRenderDrawBlendMode(
                renderer,
                SDL_BLENDMODE_BLEND
            );

            SDL_SetRenderDrawColor(
                renderer,
                0,
                0,
                0,
                static_cast<Uint8>(nightAlpha)
            );
            if (!lanternActive)
            {
                SDL_Rect nightOverlay = { 0, 0, 1280, 720 };

                SDL_RenderFillRect(
                    renderer,
                    &nightOverlay
                );
            }
            else
            {
                const int tileSize = 4;
                const int radius = 9;

                int lightLeft = 640 - 38 + 2;
                int lightTop = 360 - 38 + 2;
                if (currentPlayerTexture == playerLeftLanternTexture)
                {
                    lightLeft -= 20;
                    lightTop += 44;
                }
                else if (currentPlayerTexture == playerRightLanternTexture)
                {
                    lightLeft += 16;
                    lightTop += 44;
                }
                else if (currentPlayerTexture == playerUpLanternTexture)
                {
                    lightLeft += 32;
                    lightTop += 40;
                }
                else if (currentPlayerTexture == playerDownLanternTexture)
                {
                    lightLeft -= 32;
                    lightTop += 40;
                }


                const int outerHalfWidth[19] =
                {
                    3, 5, 6, 7, 8, 8, 9, 9, 9, 9,
                    9, 9, 9, 8, 8, 7, 6, 5, 3
                };

                const int ring60HalfWidth[19] =
                {
                    -1, -1,
                     2,  4,  5,  6,  6,  7,  7,  7,
                     7,  7,  6,  6,  5,  4,  2,
                    -1, -1
                };

                const int ring40HalfWidth[19] =
                {
                    -1, -1, -1, -1,
                     1,  3,  4,  4,  5,  5,  5,
                     4,  4,  3,  1,
                    -1, -1, -1, -1
                };

                const int ring20HalfWidth[19] =
                {
                    -1, -1, -1, -1, -1, -1,
                     1,  2,  3,  3,  3,  2,  1,
                    -1, -1, -1, -1, -1, -1
                };

                const int centerHalfWidth[19] =
                {
                    -1, -1, -1, -1, -1, -1, -1, -1,
                     1,  1,  1,
                    -1, -1, -1, -1, -1, -1, -1, -1
                };

                // Darkness above the 114x114 lantern area.
                SDL_Rect topDark =
                {
                    0,
                    0,
                    1280,
                    lightTop
                };

                SDL_RenderFillRect(
                    renderer,
                    &topDark
                );

                // Darkness below the 114x114 lantern area.
                SDL_Rect bottomDark =
                {
                    0,
                    lightTop + 76,
                    1280,
                    720 - (lightTop + 76)
                };

                SDL_RenderFillRect(
                    renderer,
                    &bottomDark
                );

                // Draw darkness on the left and right
                // of each 6-pixel row of the circle.
                for (int gridY = 0; gridY < 19; gridY++)
                {
                    int maxDx = outerHalfWidth[gridY];

                    int holeLeft =
                        lightLeft +
                        (9 - maxDx) * tileSize;

                    int holeRight =
                        lightLeft +
                        (9 + maxDx + 1) * tileSize;

                    int rowY =
                        lightTop +
                        gridY * tileSize;

                    SDL_Rect leftDark =
                    {
                        0,
                        rowY,
                        holeLeft,
                        tileSize
                    };

                    SDL_RenderFillRect(
                        renderer,
                        &leftDark
                    );

                    SDL_Rect rightDark =
                    {
                        holeRight,
                        rowY,
                        1280 - holeRight,
                        tileSize
                    };

                    SDL_RenderFillRect(
                        renderer,
                        &rightDark
                    );
                    for (
                        int gridX = 9 - maxDx;
                        gridX <= 9 + maxDx;
                        gridX++
                        )
                    {
                        int dxAbs = std::abs(gridX - 9);

                        float darknessAmount = 0.80f;

                        if (
                            centerHalfWidth[gridY] >= 0 &&
                            dxAbs <= centerHalfWidth[gridY]
                            )
                        {
                            darknessAmount = 0.00f;
                        }
                        else if (
                            ring20HalfWidth[gridY] >= 0 &&
                            dxAbs <= ring20HalfWidth[gridY]
                            )
                        {
                            darknessAmount = 0.20f;
                        }
                        else if (
                            ring40HalfWidth[gridY] >= 0 &&
                            dxAbs <= ring40HalfWidth[gridY]
                            )
                        {
                            darknessAmount = 0.40f;
                        }
                        else if (
                            ring60HalfWidth[gridY] >= 0 &&
                            dxAbs <= ring60HalfWidth[gridY]
                            )
                        {
                            darknessAmount = 0.60f;
                        }
                        else
                        {
                            darknessAmount = 0.80f;
                        }

                        Uint8 tileAlpha =
                            static_cast<Uint8>(
                                nightAlpha * darknessAmount
                                );

                        SDL_SetRenderDrawColor(
                            renderer,
                            0,
                            0,
                            0,
                            tileAlpha
                        );

                        SDL_Rect gradientTile =
                        {
                            lightLeft + gridX * tileSize,
                            rowY,
                            tileSize,
                            tileSize
                        };

                        SDL_RenderFillRect(
                            renderer,
                            &gradientTile
                        );
                    }

                    SDL_SetRenderDrawColor(
                        renderer,
                        0,
                        0,
                        0,
                        static_cast<Uint8>(nightAlpha)
                    );
                }
            }

            if (fireballActive)
            {
                const int fireLightTileSize = 4;

                int fireLightLeft =
                    fireballRect.x + 62 - 38;

                int fireLightTop =
                    fireballRect.y + 66 - 38;

                const int fireOuterHalfWidth[19] =
                {
                    3, 5, 6, 7, 8, 8, 9, 9, 9, 9,
                    9, 9, 9, 8, 8, 7, 6, 5, 3
                };

                const int fireRing60HalfWidth[19] =
                {
                    -1, -1,
                     2, 4, 5, 6, 6, 7, 7, 7,
                     7, 7, 6, 6, 5, 4, 2,
                    -1, -1
                };

                const int fireRing40HalfWidth[19] =
                {
                    -1, -1, -1, -1,
                     1, 3, 4, 4, 5, 5, 5,
                     4, 4, 3, 1,
                    -1, -1, -1, -1
                };

                const int fireRing20HalfWidth[19] =
                {
                    -1, -1, -1, -1, -1, -1,
                     1, 2, 3, 3, 3, 2, 1,
                    -1, -1, -1, -1, -1, -1
                };

                const int fireCenterHalfWidth[19] =
                {
                    -1, -1, -1, -1, -1, -1, -1, -1,
                     1, 1, 1,
                    -1, -1, -1, -1, -1, -1, -1, -1
                };

                SDL_SetRenderDrawBlendMode(
                    renderer,
                    SDL_BLENDMODE_NONE
                );

                for (int gridY = 0; gridY < 19; gridY++)
                {
                    int maxDx =
                        fireOuterHalfWidth[gridY];

                    int rowY =
                        fireLightTop +
                        gridY * fireLightTileSize;

                    for (
                        int gridX = 9 - maxDx;
                        gridX <= 9 + maxDx;
                        gridX++
                        )
                    {
                        int dxAbs =
                            std::abs(gridX - 9);

                        float darknessAmount = 0.80f;

                        if (
                            fireCenterHalfWidth[gridY] >= 0 &&
                            dxAbs <= fireCenterHalfWidth[gridY]
                            )
                        {
                            darknessAmount = 0.00f;
                        }
                        else if (
                            fireRing20HalfWidth[gridY] >= 0 &&
                            dxAbs <= fireRing20HalfWidth[gridY]
                            )
                        {
                            darknessAmount = 0.20f;
                        }
                        else if (
                            fireRing40HalfWidth[gridY] >= 0 &&
                            dxAbs <= fireRing40HalfWidth[gridY]
                            )
                        {
                            darknessAmount = 0.40f;
                        }
                        else if (
                            fireRing60HalfWidth[gridY] >= 0 &&
                            dxAbs <= fireRing60HalfWidth[gridY]
                            )
                        {
                            darknessAmount = 0.60f;
                        }

                        Uint8 fireTileAlpha =
                            static_cast<Uint8>(
                                nightAlpha * darknessAmount
                                );

                        SDL_SetRenderDrawColor(
                            renderer,
                            0,
                            0,
                            0,
                            fireTileAlpha
                        );

                        SDL_Rect fireGradientTile =
                        {
                            fireLightLeft +
                                gridX * fireLightTileSize,

                            rowY,

                            fireLightTileSize,
                            fireLightTileSize
                        };

                        SDL_RenderFillRect(
                            renderer,
                            &fireGradientTile
                        );
                    }
                }

                SDL_SetRenderDrawBlendMode(
                    renderer,
                    SDL_BLENDMODE_BLEND
                );
            }
            
            SDL_SetRenderTarget(
                renderer,
                nullptr
            );

            SDL_RenderCopy(
                renderer,
                darknessTexture,
                nullptr,
                nullptr
            );

            SDL_RenderCopy(
                renderer,
                hotbarTexture,
                nullptr,
                &hotbarRect
            );

            if (fireballActive)
            {
                SDL_RenderCopy(
                    renderer,
                    fireballTexture,
                    &fireballSourceRect,
                    &fireballRect
                );
            }

            SDL_RenderCopy(
                renderer,
                heartTexture,
                &heartSourceRect,
                &heartRect
            );

            SDL_RenderCopy(
                renderer,
                flameTexture,
                &flameSourceRect,
                &flameRect
            );

            SDL_RenderCopy(
                renderer,
                dayClockTexture,
                &dayClockSourceRect,
                &dayClockRect
            );

            lanternSourceRect.x = lanternSlot * 568;

            lanternRect.x = hotbarRect.x + 40;
            lanternRect.y = hotbarRect.y + 40;

            // Special correction for slot 9 only


            if (lanternSlot == 8)
            {
                lanternRect.x = hotbarRect.x + 37;
            }

            if (lanternSlot == 7)
            {
                lanternRect.x -= 3;
            }

            if (lanternSlot == 6)
            {
                lanternRect.x -= 3;
            }

            if (lanternSlot == 5)
            {
                lanternRect.x -= 2;
            }

            if (lanternSlot == 4)
            {
                lanternRect.x -= 2;
            }

            if (lanternSlot == 3)
            {
                lanternRect.x -= 1;
            }

            if (lanternSlot == 2)
            {
                lanternRect.x -= 1;
            }

            if (lanternSlot == 1)
            {
                lanternRect.x -= 1;
            }
            SDL_RenderCopy(
                renderer,
                lanternTexture,
                &lanternSourceRect,
                &lanternRect
            );

            pickaxeSourceRect.x = pickaxeSlot * 568;

            pickaxeRect.x = hotbarRect.x + 40;
            pickaxeRect.y = hotbarRect.y + 40;

            if (pickaxeSlot == 8)
            {
                pickaxeRect.x = hotbarRect.x + 37;
            }

            if (pickaxeSlot == 7)
            {
                pickaxeRect.x = hotbarRect.x + 37;
            }

            if (pickaxeSlot == 6)
            {
                pickaxeRect.x = hotbarRect.x + 37;
            }

            if (pickaxeSlot == 5)
            {
                pickaxeRect.x = hotbarRect.x + 37;
            }

            if (pickaxeSlot == 4)
            {
                pickaxeRect.x = hotbarRect.x + 37;
            }

            if (pickaxeSlot == 3)
            {
                pickaxeRect.x = hotbarRect.x + 39;
            }

            if (pickaxeSlot == 2)
            {
                pickaxeRect.x = hotbarRect.x + 39;
            }
            if (pickaxeSlot == 1)
            {
                pickaxeRect.x = hotbarRect.x + 39;
            }
            SDL_RenderCopy(
                renderer,
                pickaxeTexture,
                &pickaxeSourceRect,
                &pickaxeRect
            );

            if (pickaxeSlot ==8)
            {
                pickaxeRect.x += 2;
            }

            if (pickaxeSlot == 7)
            {
                pickaxeRect.x -= 7;
            }

            hotbarHighlightRect.x =
                hotbarRect.x + 32 + (selectedSlot * 63);

            hotbarHighlightRect.y =
                hotbarRect.y + 32;

            if (selectedSlot == axeSlot)
            {
                // Axe is currently selected
            }

            if (selectedSlot == 8)
            {
                hotbarHighlightRect.x += 4;
            }

            if (selectedSlot == 7)
            {
                hotbarHighlightRect.x += 4;
            }

            if (selectedSlot == 6)
            {
                hotbarHighlightRect.x += 3;
            }

            if (selectedSlot == 5)
            {
                hotbarHighlightRect.x += 3;
            }

            if (selectedSlot == 4)
            {
                hotbarHighlightRect.x += 2;
            }

            if (selectedSlot == 3)
            {
                hotbarHighlightRect.x += 2;
            }

            if (selectedSlot == 2)
            {
                hotbarHighlightRect.x += 1;
            }

            axeSourceRect.x = axeSlot * 568;

            axeRect.x = hotbarRect.x + 40;
            axeRect.y = hotbarRect.y + 40;

            if (axeSlot == 8)
            {
                axeRect.x = hotbarRect.x + 37;
            }
            if (axeSlot == 7)
            {
                axeRect.x = hotbarRect.x + 37;
            }
            if (axeSlot == 6)
            {
                axeRect.x = hotbarRect.x + 37;
            }
            if (axeSlot == 5)
            {
                axeRect.x = hotbarRect.x + 38;
            }
            if (axeSlot == 4)
            {
                axeRect.x = hotbarRect.x + 37;
            }
            if (axeSlot == 3)
            {
                axeRect.x = hotbarRect.x + 39;
            }
            if (axeSlot == 2)
            {
                axeRect.x = hotbarRect.x + 39;
            }
            if (axeSlot == 1)
            {
                axeRect.x = hotbarRect.x + 39;
            }

            SDL_RenderCopy(
                renderer,
                axeTexture,
                &axeSourceRect,
                &axeRect
            );


            SDL_RenderCopy(
                renderer,
                hotbarHighlightTexture,
                &hotbarHighlightSource,
                &hotbarHighlightRect
            );
        }

        // Display the completed frame.
        SDL_RenderPresent(renderer);

    }

    // Cleanup after the game loop ends.
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(titleTexture);
    SDL_DestroyTexture(textTexture);

    SDL_DestroyTexture(playerDownLanternTexture);
    SDL_DestroyTexture(playerUpLanternTexture);
    SDL_DestroyTexture(playerLeftLanternTexture);
    SDL_DestroyTexture(playerRightLanternTexture);

    SDL_DestroyTexture(playerDownAxeTexture);
    SDL_DestroyTexture(playerUpAxeTexture);
    SDL_DestroyTexture(playerLeftAxeTexture);
    SDL_DestroyTexture(playerRightAxeTexture);

    TTF_CloseFont(titleFont);
    TTF_CloseFont(font);

    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}