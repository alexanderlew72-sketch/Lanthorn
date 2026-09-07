#include <SDL2/SDL.h>

#include <SDL_ttf.h>

#include <SDL_image.h>

#include <iostream>

#include <filesystem>
#include <cstdlib>
#include <ctime>

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
        SDL_RENDERER_ACCELERATED
    );

    SDL_RenderSetLogicalSize(
        renderer,
        1280,
        720
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
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/background.png"
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

    SDL_Texture* tree1Texture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/Tree1-Sheet.png"
    );

    if (tree1Texture == nullptr)
    {
        std::cout << "Tree 1 failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* tree2Texture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/Tree2-Sheet.png"
    );

    SDL_Texture* treeFallingRightTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/TreeFallingRight-Sheet.png"
    );

    SDL_Texture* treeFallingLeftTexture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/TreeFallingLeft-Sheet.png"
    );

    if (treeFallingLeftTexture == nullptr)
    {
        std::cout << "Tree falling left failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    SDL_Texture* stump1Texture = IMG_LoadTexture(
        renderer,
        "C:/Users/lewir/source/repos/Lanthorn/Lanthorn/assets/Stump1-Sheet.png"
    );

    if (stump1Texture == nullptr)
    {
        std::cout << "Stump 1 failed to load: "
            << IMG_GetError()
            << std::endl;
    }

    if (treeFallingRightTexture == nullptr)
    {
        std::cout << "Tree falling right failed to load: "
            << IMG_GetError()
            << std::endl;
    }
    if (tree2Texture == nullptr)
    {
        std::cout << "Tree 2 failed to load: "
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

    SDL_Rect treeRects[6];
    SDL_Rect treeCollisionRects[6];
    int treeTypes[6];

    int treeHits[6] = { 0, 0, 0, 0, 0, 0 };
    bool treeFalling[6] = { false, false, false, false, false, false };
    bool treeFallen[6] = { false, false, false, false, false, false };
    int treeFallFrame[6] = { 0, 0, 0, 0, 0, 0 };

    int treeFallDirection[6] = { 0, 0, 0, 0, 0, 0 };

    bool treeRandomFall[6] =
    {
        false, false, false,
        false, false, false
    };

    for (int i = 0; i < 6; i++)
    {
        treeRects[i].w = 140;
        treeRects[i].h = 356;

        treeRects[i].x = 100 + (std::rand() % 1080);
        treeRects[i].y = 50 + (std::rand() % 450);

        treeTypes[i] = std::rand() % 2;


        // TREE COLLISION RECTANGLE
        treeCollisionRects[i].w = 56;
            treeCollisionRects[i].h = 56;

        // Center the collision box horizontally
        treeCollisionRects[i].x =
            treeRects[i].x + (treeRects[i].w - treeCollisionRects[i].w) / 2;

        // Put the collision box at the very bottom of the tree
        treeCollisionRects[i].y =
            treeRects[i].y + treeRects[i].h - treeCollisionRects[i].h;
    
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

    // This selects which 32x32 frame of the sprite sheet to show
    SDL_Rect playerSourceRect;

    playerSourceRect.x = 0;
    playerSourceRect.y = 0;
    playerSourceRect.w = 32;
    playerSourceRect.h = 32;

    SDL_Rect playerCollisionRect;

    playerCollisionRect.w = 40;
    playerCollisionRect.h = 16;


    // This controls WHERE and HOW LARGE the player appears on screen
    SDL_Rect player;

    player.w = 96;
    player.h = 96;


    // Smooth player position
    float playerX = 615.0f;
    float playerY = 335.0f;


    // Movement speed
    float playerSpeed = .2f;

    bool isMoving = false;

    int playerDirection = 0;


    // Put the float position into the SDL rectangle
    player.x = static_cast<int>(playerX);
    player.y = static_cast<int>(playerY);

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
        

            // AXE HIT WITH R
            if (
                event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_r &&
                event.key.repeat == 0
                )
            {
                if (selectedSlot == axeSlot)
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

    for (int i = 0; i < 6; i++)
    {
       

        if (treeTypes[i] == 0 &&
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
                treeFallDirection[i] = 0;
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

                        for (int i = 0; i < 6; i++)
                        {
                            // treeTypes[i] == 0 means Tree 1
                            if (treeTypes[i] == 0 && !treeFalling[i])
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
                                    treeFallDirection[i] = 0;
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

                        for (int i = 0; i < 6; i++)
                        {
                            if (treeTypes[i] == 0 &&
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

                        for (int i = 0; i < 6; i++)
                        {
                            if (treeTypes[i] == 0 &&
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

                for (int i = 0; i < 6; i++)
                {
                    if (CheckCollision(
                        nextPlayerCollisionRect,
                        treeCollisionRects[i]
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

                for (int i = 0; i < 6; i++)
                {
                    if (CheckCollision(
                        nextPlayerCollisionRect,
                        treeCollisionRects[i]
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

                for (int i = 0; i < 6; i++)
                {
                    if (CheckCollision(
                        nextPlayerCollisionRect,
                        treeCollisionRects[i]
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

                for (int i = 0; i < 6; i++)
                {
                    if (CheckCollision(
                        nextPlayerCollisionRect,
                        treeCollisionRects[i]
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

        if (currentTime - lastTreeFallTime >= treeFallFrameDelay)
        {
            for (int i = 0; i < 6; i++)
            {
                if (treeFalling[i])
                {
                    treeFallFrame[i]++;

                    if (treeFallFrame[i] >= 7)
                    {
                        treeFallFrame[i] = 6;
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

            SDL_RenderCopy(
                renderer,
                backgroundTexture,
                nullptr,
                nullptr
            );

            // FIRST TREE PASS
// Draw normal trees behind the player.
// Draw falling trees and stumps normally.

            for (int i = 0; i < 6; i++)
            {
                // FALLEN TREE = STUMP ONLY
                if (treeFallen[i])
                {
                    SDL_Rect stumpRect;

                    stumpRect.w = 140;
                    stumpRect.h = 356;

                    stumpRect.x = treeRects[i].x;
                    stumpRect.y = treeRects[i].y;

                    SDL_RenderCopy(
                        renderer,
                        stump1Texture,
                        nullptr,
                        &stumpRect
                    );
                }

                // TREE IS CURRENTLY FALLING
                else if (treeFalling[i])
                {
                    SDL_Rect treeFallSourceRect;

                    treeFallSourceRect.x = treeFallFrame[i] * 104;
                    treeFallSourceRect.y = 0;
                    treeFallSourceRect.w = 104;
                    treeFallSourceRect.h = 89;

                    SDL_Rect treeFallRect;

                    treeFallRect.w = 416;
                    treeFallRect.h = 356;

                    if (treeFallDirection[i] == 0)
                    {
                        // Falling RIGHT:
                        // first 35 pixels stay lined up with original tree
                        treeFallRect.x = treeRects[i].x;
                    }
                    else
                    {
                        // Falling LEFT:
                        // last 35 pixels stay lined up with original tree
                        treeFallRect.x =
                            treeRects[i].x - ((104 - 35) * 4);
                    }

                    treeFallRect.y = treeRects[i].y;
                    SDL_Texture* fallingTexture;

                    if (treeFallDirection[i] == 0)
                    {
                        fallingTexture = treeFallingRightTexture;
                    }
                    else
                    {
                        fallingTexture = treeFallingLeftTexture;
                    }

                    SDL_RenderCopy(
                        renderer,
                        fallingTexture,
                        &treeFallSourceRect,
                        &treeFallRect
                    );
                }

                // TREE IS STILL STANDING
                else
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
                            treeTexture = tree1Texture;
                        }
                        else
                        {
                            treeTexture = tree2Texture;
                        }

                        SDL_SetTextureAlphaMod(treeTexture, 255);

                        SDL_RenderCopy(
                            renderer,
                            treeTexture,
                            nullptr,
                            &treeRects[i]
                        );
                    }
                }
            }
            // Draw the player.
            SDL_RenderCopy(
                renderer,
                currentPlayerTexture,
                &playerSourceRect,
                &player
            );

            // SECOND TREE PASS
            // Only standing trees can become transparent.

            for (int i = 0; i < 6; i++)
            {
                if (!treeFalling[i] && !treeFallen[i])
                {
                    bool playerUnderTree =
                        CheckCollision(player, treeRects[i]) &&
                        !CheckCollision(player, treeCollisionRects[i]);

                    if (playerUnderTree)
                    {
                        SDL_Texture* treeTexture;

                        if (treeTypes[i] == 0)
                        {
                            treeTexture = tree1Texture;
                        }
                        else
                        {
                            treeTexture = tree2Texture;
                        }

                        SDL_SetTextureAlphaMod(treeTexture, 128);

                        SDL_RenderCopy(
                            renderer,
                            treeTexture,
                            nullptr,
                            &treeRects[i]
                        );

                        SDL_SetTextureAlphaMod(treeTexture, 255);
                    }
                }
            }
            SDL_RenderCopy(
                renderer,
                hotbarTexture,
                nullptr,
                &hotbarRect
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