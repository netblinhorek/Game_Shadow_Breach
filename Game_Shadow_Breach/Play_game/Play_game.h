#pragma once

namespace CppCLRWinFormsProject {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class GameCharacter
    {
    public:
        property int X;
        property int Y;
        property int Health;
        property float Speed;
        property String^ Name;

        GameCharacter(int x, int y, int health, float speed, String^ name)
        {
            X = x;
            Y = y;
            Health = health;
            Speed = speed;
            Name = name;
        }

        void Move(int deltaX, int deltaY)
        {
            X += deltaX;
            Y += deltaY;
        }
    };

    /// <summary>
    /// Summary for Play_game
    /// </summary>
    public ref class Play_game : public System::Windows::Forms::Form
    {
    public:
        Play_game(void)
        {
            InitializeComponent();
            InitializePanels();
            LoadBackgroundImage();
            InitializePlayer();
            InitializeEnemy();
            HideAllPanels();
        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~Play_game()
        {
            if (components)
            {
                delete components;
            }
            if (playerSprite != nullptr)
            {
                delete playerSprite;
            }
            if (enemySprite != nullptr)
            {
                delete enemySprite;
            }
        }

    private:
        System::Windows::Forms::Button^ buttonExit;
        System::Windows::Forms::Button^ buttonStatus;
        System::Windows::Forms::Button^ buttonBackpack;
        System::Windows::Forms::PictureBox^ pictureBox1;
        System::Windows::Forms::Panel^ panelStatus;
        System::Windows::Forms::Panel^ panelBackpack;
        System::Windows::Forms::Button^ buttonCloseStatus;
        System::Windows::Forms::Button^ buttonCloseBackpack;
        System::Windows::Forms::PictureBox^ playerSprite;
        System::Windows::Forms::PictureBox^ enemySprite;

        // Простой класс персонажа вместо абстрактного Character
        GameCharacter^ playerCharacter;
        GameCharacter^ enemyCharacter;

        // Дополнительно: несколько врагов
        System::Collections::Generic::List<GameCharacter^>^ enemies;
        System::Collections::Generic::List<System::Windows::Forms::PictureBox^>^ enemySprites;
        int totalEnemiesToSpawn;
        int totalEnemiesCap;
        int spawnedEnemiesCount;
        int enemiesAlive;
        System::Windows::Forms::Timer^ spawnTimer;

        // UI элементы состояния/рюкзака
        System::Windows::Forms::Label^ labelHealthStatus;
        System::Windows::Forms::ListBox^ backpackList;
        System::Windows::Forms::Panel^ tutorialPanel;
        System::Windows::Forms::Label^ tutorialLabel;
        System::Windows::Forms::Button^ tutorialNextButton;

        // Обучение и бой
        bool tutorialCompleted;
        int tutorialStep;
        bool hasGun;
        int baseDamage;
        int enemyHealth;
        System::Windows::Forms::Timer^ enemyTimer;
        System::Random^ rng;

        // Направление и анимация игрока
        enum class Direction { Up, Right, Down, Left };
        Direction playerDirection;
        bool isMoving;
        bool useRightStep;
        Timer^ playerAnimTimer;
        Timer^ playerAttackTimer;

        // Кадры игрока (idle и шаги)
        Bitmap^ idleUp;    Bitmap^ idleRight; Bitmap^ idleDown;  Bitmap^ idleLeft;
        Bitmap^ stepUpRight;    Bitmap^ stepUpLeft;
        Bitmap^ stepRightRight; Bitmap^ stepRightLeft;
        Bitmap^ stepDownRight;  Bitmap^ stepDownLeft;
        Bitmap^ stepLeftRight;  Bitmap^ stepLeftLeft;
        // Кадры атаки (с пушкой)
        Bitmap^ attackUp; Bitmap^ attackRight; Bitmap^ attackDown; Bitmap^ attackLeft;

        // Спрайты врагов и эффект взрыва
        Bitmap^ enemyBaseImage;
        Bitmap^ explosionImage;
        System::Collections::Generic::List<System::Windows::Forms::PictureBox^>^ explosionSprites;
        System::Collections::Generic::List<int>^ explosionTicks;
        System::Windows::Forms::Timer^ explosionTimer;

    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        System::ComponentModel::Container^ components;

        void LoadBackgroundImage()
        {
            try
            {
                array<String^>^ possiblePaths = {
                    "поле.png"
                };

                bool imageLoaded = false;
                for each (String ^ path in possiblePaths)
                {
                    if (System::IO::File::Exists(path))
                    {
                        pictureBox1->Image = Image::FromFile(path);
                        pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
                        pictureBox1->Dock = DockStyle::Fill; 
                        imageLoaded = true;
                        break;
                    }
                }

                if (!imageLoaded)
                {
                    pictureBox1->BackColor = Color::LightGray;
                    MessageBox::Show("Фоновое изображение не найдено!", "Предупреждение",
                        MessageBoxButtons::OK, MessageBoxIcon::Warning);
                }
            }
            catch (Exception^ ex)
            {
                pictureBox1->BackColor = Color::LightGray;
                MessageBox::Show("Ошибка загрузки изображения: " + ex->Message,
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        
        Bitmap^ LoadBmpTransparentWhite(String^ path)
        {
            if (!System::IO::File::Exists(path)) return nullptr;
            Bitmap^ bmp = gcnew Bitmap(Image::FromFile(path));
            bmp->MakeTransparent(Color::White);
            return bmp;
        }
        
         void LoadPlayerImages()
         {
             // Стоит (idle)
             idleUp = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\W.jpg");
             idleRight = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\D.png");
             idleDown = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\S.png");
             idleLeft = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\A.png");
 
             // Шаги
             stepUpRight   = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\игрок_шаг_правой_W.png");
             stepUpLeft    = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\игрок_шаг_левой_W.png");
             stepRightRight= LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\игрок_шаг_правой_D.png");
             stepRightLeft = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\игрок_шаг_левой_D.png");
             stepDownRight = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\игрок_шаг_правой_S.png");
             stepDownLeft  = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\игрок_шаг_левой_S.png");
             stepLeftRight = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\игрок_шаг_правой_A.png");
             stepLeftLeft  = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\игрок_шаг_левой_A.png");

             // Атака
             attackUp = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\игрок_с_пушкой_W.png");
             attackRight = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\игрок_с_пушкой_D.png");
             attackDown = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\игрок_с_пушкой_S.png");
             attackLeft = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\игрок_с_пушкой_A.png");
         }

        void UpdatePlayerImage()
        {
            if (!isMoving)
            {
                switch (playerDirection)
                {
                case Direction::Up:    if (idleUp) playerSprite->Image = idleUp; break;
                case Direction::Right: if (idleRight) playerSprite->Image = idleRight; break;
                case Direction::Down:  if (idleDown) playerSprite->Image = idleDown; break;
                case Direction::Left:  if (idleLeft) playerSprite->Image = idleLeft; break;
                }
                return;
            }

            switch (playerDirection)
            {
            case Direction::Up:
                playerSprite->Image = useRightStep && stepUpRight ? stepUpRight : (stepUpLeft ? stepUpLeft : idleUp);
                break;
            case Direction::Right:
                playerSprite->Image = useRightStep && stepRightRight ? stepRightRight : (stepRightLeft ? stepRightLeft : idleRight);
                break;
            case Direction::Down:
                playerSprite->Image = useRightStep && stepDownRight ? stepDownRight : (stepDownLeft ? stepDownLeft : idleDown);
                break;
            case Direction::Left:
                playerSprite->Image = useRightStep && stepLeftRight ? stepLeftRight : (stepLeftLeft ? stepLeftLeft : idleLeft);
                break;
            }
        }

        void InitializePlayer()
        {
            playerCharacter = gcnew GameCharacter(400, 300, 100, 5.0f, "Player");

            playerSprite = gcnew PictureBox();
            playerSprite->Size = System::Drawing::Size(50, 50);
            playerSprite->Location = System::Drawing::Point(playerCharacter->X, playerCharacter->Y);
            playerSprite->BackColor = Color::Transparent;
            playerSprite->BackgroundImage = nullptr;
            playerSprite->BackgroundImageLayout = ImageLayout::None;

            try
            {
                LoadPlayerImages();
                playerDirection = Direction::Down;
                isMoving = false;
                useRightStep = true;
                hasGun = false;
                baseDamage = 10;
                enemyHealth = 50;
                tutorialCompleted = false;
                tutorialStep = 0;
                rng = gcnew System::Random();
                if (idleDown != nullptr)
                {
                    playerSprite->Image = idleDown;
                    playerSprite->SizeMode = PictureBoxSizeMode::StretchImage;
                }
                else
                {
                    playerSprite->BackColor = Color::Transparent;
                    Label^ playerLabel = gcnew Label();
                    playerLabel->Text = "P";
                    playerLabel->Font = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
                    playerLabel->ForeColor = Color::Blue;
                    playerLabel->BackColor = Color::Transparent;
                    playerLabel->Dock = DockStyle::Fill;
                    playerLabel->TextAlign = ContentAlignment::MiddleCenter;
                    playerSprite->Controls->Add(playerLabel);
                }
            }
            catch (Exception^)
            {
                playerSprite->BackColor = Color::Transparent;
                Label^ playerLabel = gcnew Label();
                playerLabel->Text = "P";
                playerLabel->Font = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
                playerLabel->ForeColor = Color::Blue;
                playerLabel->BackColor = Color::Transparent;
                playerLabel->Dock = DockStyle::Fill;
                playerLabel->TextAlign = ContentAlignment::MiddleCenter;
                playerSprite->Controls->Add(playerLabel);
            }

            playerSprite->Parent = pictureBox1;
            pictureBox1->Controls->Add(playerSprite);
            playerSprite->BringToFront();
            this->KeyPreview = true;
            this->KeyDown += gcnew KeyEventHandler(this, &Play_game::Form_KeyDown);
            this->KeyUp += gcnew KeyEventHandler(this, &Play_game::Form_KeyUp);

            playerAnimTimer = gcnew Timer();
            playerAnimTimer->Interval = 150;
            playerAnimTimer->Tick += gcnew EventHandler(this, &Play_game::PlayerAnimTimer_Tick);
            playerAnimTimer->Start();

            // Таймер краткой анимации атаки (возврат к обычному спрайту)
            playerAttackTimer = gcnew Timer();
            playerAttackTimer->Interval = 180;
            playerAttackTimer->Tick += gcnew EventHandler(this, &Play_game::PlayerAttackTimer_Tick);

            // Создание улучшенного окна обучения
            tutorialPanel = gcnew Panel();
            tutorialPanel->Size = System::Drawing::Size(600, 150);
            tutorialPanel->Location = System::Drawing::Point((this->ClientSize.Width - tutorialPanel->Width)/2, (this->ClientSize.Height - tutorialPanel->Height)/2);
            tutorialPanel->BackColor = Color::FromArgb(230, 20, 20, 20);
            tutorialPanel->BorderStyle = BorderStyle::FixedSingle;
            tutorialPanel->ForeColor = Color::White;

            tutorialLabel = gcnew Label();
            tutorialLabel->BackColor = Color::FromArgb(230, 20, 20, 20);
            tutorialLabel->ForeColor = Color::White;
            tutorialLabel->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
            tutorialLabel->Location = System::Drawing::Point(20, 20);
            tutorialLabel->Size = System::Drawing::Size(560, 80);
            tutorialLabel->TextAlign = ContentAlignment::MiddleCenter;

            tutorialNextButton = gcnew Button();
            tutorialNextButton->Text = "Продолжить";
            tutorialNextButton->Size = System::Drawing::Size(110, 30);
            tutorialNextButton->Location = System::Drawing::Point((tutorialPanel->Width - tutorialNextButton->Width)/2, 105);
            tutorialNextButton->BackColor = Color::FromArgb(60, 60, 60);
            tutorialNextButton->ForeColor = Color::White;
            tutorialNextButton->FlatStyle = FlatStyle::Flat;
            tutorialNextButton->FlatAppearance->BorderColor = Color::Gray;
            tutorialNextButton->FlatAppearance->BorderSize = 1;
            tutorialNextButton->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
            tutorialNextButton->Cursor = Cursors::Hand;
            tutorialNextButton->Click += gcnew EventHandler(this, &Play_game::TutorialNext_Click);

            tutorialPanel->Controls->Add(tutorialLabel);
            tutorialPanel->Controls->Add(tutorialNextButton);
            this->Controls->Add(tutorialPanel);
            tutorialPanel->BringToFront();
            // гарантируем, что верхние кнопки доступны поверх панели
            buttonExit->BringToFront();
            buttonStatus->BringToFront();
            buttonBackpack->BringToFront();
            this->Resize += gcnew EventHandler(this, &Play_game::Play_game_Resize);
            ShowTutorialStep();
        }

        void ShowTutorialStep()
        {
            switch (tutorialStep)
            {
            case 0:
                tutorialLabel->Text = "Добро пожаловать в Shadow Breach!\nИспользуйте клавиши WASD или стрелки для перемещения по миру";
                break;
            case 1:
                tutorialLabel->Text = "В мире вас ждут опасные противники\nНажмите ПРОБЕЛ для атаки, когда приблизитесь к врагу";
                break;
            case 2:
                tutorialLabel->Text = "Собирайте предметы и используйте их клавишей E\nЗелья восстановят здоровье, а оружие увеличит урон";
                break;
            case 3:
                tutorialLabel->Text = "Следите за своим состоянием через меню статистики\nРюкзак поможет управлять собранными предметами";
                break;
            case 4:
                tutorialLabel->Text = "Обучение завершено! Теперь вы готовы к приключениям.";
                tutorialNextButton->Text = "Начать игру";
                break;
            case 5:
                tutorialCompleted = true;
                tutorialPanel->Visible = false;
                // Спавним одного сразу, остальные по таймеру 7с
                if (enemiesAlive < totalEnemiesToSpawn && spawnedEnemiesCount < totalEnemiesCap) SpawnOneEnemy();
                enemyTimer->Start();
                spawnTimer->Start();
                // кнопки поверх
                buttonExit->BringToFront();
                buttonStatus->BringToFront();
                buttonBackpack->BringToFront();
                break;
            }
        }

        System::Void TutorialNext_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (tutorialStep < 5)
            {
                tutorialStep++;
                ShowTutorialStep();
                if (tutorialStep == 4)
                    tutorialNextButton->Text = "Начать игру";
            }
            else
            {
                tutorialCompleted = true;
                tutorialPanel->Visible = false;
                if (enemiesAlive < totalEnemiesToSpawn && spawnedEnemiesCount < totalEnemiesCap) SpawnOneEnemy();
                enemyTimer->Start();
                spawnTimer->Start();
                buttonExit->BringToFront();
                buttonStatus->BringToFront();
                buttonBackpack->BringToFront();
            }
        }

        void InitializeEnemy()
        {
            // Коллекции врагов
            enemies = gcnew System::Collections::Generic::List<GameCharacter^>();
            enemySprites = gcnew System::Collections::Generic::List<System::Windows::Forms::PictureBox^>();
            totalEnemiesToSpawn = 3; // одновременно максимум 3 на поле
            totalEnemiesCap = 15;    // всего за игру не более 15
            spawnedEnemiesCount = 0; 
            enemiesAlive = 0;

            // Таймер для движения врагов (все сразу)
            enemyTimer = gcnew Timer();
            enemyTimer->Interval = 60;
            enemyTimer->Tick += gcnew EventHandler(this, &Play_game::EnemyTimer_Tick);

            // Таймер спавна врагов (после обучения)
            spawnTimer = gcnew Timer();
            spawnTimer->Interval = 7000; // 7 секунд между спавнами
            spawnTimer->Tick += gcnew EventHandler(this, &Play_game::SpawnTimer_Tick);

            // Загрузка изображений врага и взрыва
            String^ enemyImagePath = "враг.png";
            if (System::IO::File::Exists(enemyImagePath))
            {
                enemyBaseImage = gcnew Bitmap(Image::FromFile(enemyImagePath));
                enemyBaseImage->MakeTransparent(Color::White);
            }
            String^ explosionPath = "взрыв_при_попадании.png";
            if (System::IO::File::Exists(explosionPath))
            {
                explosionImage = gcnew Bitmap(Image::FromFile(explosionPath));
                // Прозрачность по цвету углового пикселя (фон)
                try { Color key = explosionImage->GetPixel(0, 0); explosionImage->MakeTransparent(key); } catch (...) { explosionImage->MakeTransparent(Color::White); }
            }

            explosionSprites = gcnew System::Collections::Generic::List<System::Windows::Forms::PictureBox^>();
            explosionTicks = gcnew System::Collections::Generic::List<int>();
            explosionTimer = gcnew Timer();
            explosionTimer->Interval = 60;
            explosionTimer->Tick += gcnew EventHandler(this, &Play_game::ExplosionTimer_Tick);
        }

        void SpawnOneEnemy()
        {
            if (enemiesAlive >= totalEnemiesToSpawn) return;
            if (spawnedEnemiesCount >= totalEnemiesCap) return;
            int ex, ey;
            int attempts = 0;
            // Спавним на расстоянии от игрока и подальше от других врагов
            do {
                ex = rng->Next(50, this->ClientSize.Width - 100);
                ey = rng->Next(100, this->ClientSize.Height - 120);
                attempts++;
                bool tooCloseToPlayer = (System::Math::Abs(ex - playerCharacter->X) < 220 && System::Math::Abs(ey - playerCharacter->Y) < 220);
                bool tooCloseToOthers = false;
                for (int i = 0; i < enemies->Count && !tooCloseToOthers; ++i)
                {
                    int dx = enemies[i]->X - ex;
                    int dy = enemies[i]->Y - ey;
                    if (dx*dx + dy*dy < 65*65) tooCloseToOthers = true; // не перекрывать спавн
                }
                if (!tooCloseToPlayer && !tooCloseToOthers) break;
            } while (attempts < 50);

            GameCharacter^ e = gcnew GameCharacter(ex, ey, 60, 2.0f, "Enemy");
            PictureBox^ sprite = gcnew PictureBox();
            sprite->Size = System::Drawing::Size(50, 50);
            sprite->Location = System::Drawing::Point(e->X, e->Y);
            sprite->BackColor = Color::Transparent;
            if (enemyBaseImage != nullptr)
            {
                sprite->Image = enemyBaseImage;
                sprite->SizeMode = PictureBoxSizeMode::StretchImage;
            }
            else
            {
                Label^ enemyLabel = gcnew Label();
                enemyLabel->Text = "E";
                enemyLabel->Font = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
                enemyLabel->ForeColor = Color::Red;
                enemyLabel->BackColor = Color::Transparent;
                enemyLabel->Dock = DockStyle::Fill;
                enemyLabel->TextAlign = ContentAlignment::MiddleCenter;
                sprite->Controls->Add(enemyLabel);
            }
            sprite->Parent = pictureBox1;
            pictureBox1->Controls->Add(sprite);
            sprite->BringToFront();

            enemies->Add(e);
            enemySprites->Add(sprite);
            enemiesAlive++;
            spawnedEnemiesCount++;
        }

       void InitializePanels()
        {
            panelStatus = gcnew Panel();
            panelStatus->Size = System::Drawing::Size(200, 150);
            panelStatus->Location = System::Drawing::Point(750, 50);
            panelStatus->BackColor = Color::FromArgb(180, 20, 20, 20);
            panelStatus->BorderStyle = BorderStyle::FixedSingle;
            panelStatus->Visible = false;

            buttonCloseStatus = gcnew Button();
            buttonCloseStatus->Text = "X";
            buttonCloseStatus->Size = System::Drawing::Size(25, 25);
            buttonCloseStatus->Location = System::Drawing::Point(panelStatus->Width - 30, 5);
            buttonCloseStatus->BackColor = Color::LightCoral;
            buttonCloseStatus->ForeColor = Color::White;
            buttonCloseStatus->Click += gcnew EventHandler(this, &Play_game::buttonCloseStatus_Click);

            Label^ labelStatus = gcnew Label();
            labelStatus->Text = "Статистика";
            labelStatus->Location = System::Drawing::Point(10, 10);
            labelStatus->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12, FontStyle::Bold);
            labelStatus->AutoSize = true;
            labelStatus->ForeColor = Color::White;

            labelHealthStatus = gcnew Label();
            labelHealthStatus->Text = "Здоровье: 100%";
            labelHealthStatus->Location = System::Drawing::Point(20, 50);
            labelHealthStatus->AutoSize = true;
            labelHealthStatus->ForeColor = Color::LightGreen;

            Label^ labelMana = gcnew Label();
            labelMana->Text = "Мана: 100%";
            labelMana->Location = System::Drawing::Point(20, 80);
            labelMana->AutoSize = true;
            labelMana->ForeColor = Color::SkyBlue;

            panelStatus->Controls->Add(buttonCloseStatus);
            panelStatus->Controls->Add(labelStatus);
            panelStatus->Controls->Add(labelHealthStatus);
            panelStatus->Controls->Add(labelMana);

           
            panelBackpack = gcnew Panel();
            panelBackpack->Size = System::Drawing::Size(200, 150);
            panelBackpack->Location = System::Drawing::Point(1100, 100);
            panelBackpack->BackColor = Color::FromArgb(180, 20, 20, 20);
            panelBackpack->BorderStyle = BorderStyle::FixedSingle;
            panelBackpack->Visible = false;

            buttonCloseBackpack = gcnew Button();
            buttonCloseBackpack->Text = "X";
            buttonCloseBackpack->Size = System::Drawing::Size(25, 25);
            buttonCloseBackpack->Location = System::Drawing::Point(panelBackpack->Width - 30, 5);
            buttonCloseBackpack->BackColor = Color::LightCoral;
            buttonCloseBackpack->ForeColor = Color::White;
            buttonCloseBackpack->Click += gcnew EventHandler(this, &Play_game::buttonCloseBackpack_Click);

            Label^ labelBackpack = gcnew Label();
            labelBackpack->Text = "Рюкзак";
            labelBackpack->Location = System::Drawing::Point(10, 10);
            labelBackpack->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12, FontStyle::Bold);
            labelBackpack->AutoSize = true;
            labelBackpack->ForeColor = Color::White;

            backpackList = gcnew ListBox();
            backpackList->Location = System::Drawing::Point(20, 40);
            backpackList->Size = System::Drawing::Size(160, 100);
            backpackList->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 9);
            backpackList->BackColor = Color::FromArgb(30,30,30);
            backpackList->ForeColor = Color::White;

            panelBackpack->Controls->Add(buttonCloseBackpack);
            panelBackpack->Controls->Add(labelBackpack);
            panelBackpack->Controls->Add(backpackList);

           
            this->Controls->Add(panelStatus);
            this->Controls->Add(panelBackpack);
        }

        void HideAllPanels()
        {
            panelStatus->Visible = false;
            panelBackpack->Visible = false;
        }

        void MovePlayer(int deltaX, int deltaY)
        {
            playerCharacter->Move(deltaX, deltaY);

            playerSprite->Location = System::Drawing::Point(
                playerCharacter->X,
                playerCharacter->Y
            );
        }

        void MoveEnemyTowardsPlayer()
        {
            int playerX = playerCharacter->X;
            int playerY = playerCharacter->Y;
            int enemyX = enemyCharacter->X;
            int enemyY = enemyCharacter->Y;

            int deltaX = 0;
            int deltaY = 0;

            if (enemyX < playerX) deltaX = 1;
            else if (enemyX > playerX) deltaX = -1;

            if (enemyY < playerY) deltaY = 1;
            else if (enemyY > playerY) deltaY = -1;

            enemyCharacter->Move(deltaX * 2, deltaY * 2); 

            enemySprite->Location = System::Drawing::Point(
                enemyCharacter->X,
                enemyCharacter->Y
            );
        }

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent(void)
        {
            this->buttonExit = (gcnew System::Windows::Forms::Button());
            this->buttonStatus = (gcnew System::Windows::Forms::Button());
            this->buttonBackpack = (gcnew System::Windows::Forms::Button());
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
            this->SuspendLayout();

            // buttonExit 
            this->buttonExit->Location = System::Drawing::Point(5, 5);
            this->buttonExit->Name = L"buttonExit";
            this->buttonExit->Size = System::Drawing::Size(150, 75);
            this->buttonExit->TabIndex = 0;
            this->buttonExit->Text = L"Выход";
            this->buttonExit->UseVisualStyleBackColor = true;
            this->buttonExit->BackColor = System::Drawing::Color::FromArgb(30,30,30);
            this->buttonExit->ForeColor = System::Drawing::Color::White;
            this->buttonExit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonExit->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(80,80,80);
            this->buttonExit->FlatAppearance->BorderSize = 1;
            this->buttonExit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold));
            this->buttonExit->Cursor = System::Windows::Forms::Cursors::Hand;
            this->buttonExit->Click += gcnew System::EventHandler(this, &Play_game::buttonExit_Click);

            // buttonStatus 
            this->buttonStatus->Location = System::Drawing::Point(1150, 5);
            this->buttonStatus->Name = L"buttonStatus";
            this->buttonStatus->Size = System::Drawing::Size(150, 75);
            this->buttonStatus->TabIndex = 1;
            this->buttonStatus->Text = L"Статистика";
            this->buttonStatus->UseVisualStyleBackColor = true;
            this->buttonStatus->BackColor = System::Drawing::Color::FromArgb(30,30,30);
            this->buttonStatus->ForeColor = System::Drawing::Color::White;
            this->buttonStatus->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonStatus->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(80,80,80);
            this->buttonStatus->FlatAppearance->BorderSize = 1;
            this->buttonStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold));
            this->buttonStatus->Cursor = System::Windows::Forms::Cursors::Hand;
            this->buttonStatus->Click += gcnew System::EventHandler(this, &Play_game::buttonStatus_Click);

            // buttonBackpack 
            this->buttonBackpack->Location = System::Drawing::Point(1150, 720);
            this->buttonBackpack->Name = L"buttonBackpack";
            this->buttonBackpack->Size = System::Drawing::Size(150, 75);
            this->buttonBackpack->TabIndex = 3;
            this->buttonBackpack->Text = L"Рюкзак";
            this->buttonBackpack->UseVisualStyleBackColor = true;
            this->buttonBackpack->BackColor = System::Drawing::Color::FromArgb(30,30,30);
            this->buttonBackpack->ForeColor = System::Drawing::Color::White;
            this->buttonBackpack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonBackpack->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(80,80,80);
            this->buttonBackpack->FlatAppearance->BorderSize = 1;
            this->buttonBackpack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold));
            this->buttonBackpack->Cursor = System::Windows::Forms::Cursors::Hand;
            this->buttonBackpack->Click += gcnew System::EventHandler(this, &Play_game::buttonBackpack_Click);

            // pictureBox1 
            this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
            this->pictureBox1->Location = System::Drawing::Point(0, 0);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(1300, 800);
            this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
            this->pictureBox1->TabIndex = 4;
            this->pictureBox1->TabStop = false;
            this->pictureBox1->BackColor = System::Drawing::Color::Transparent;

            // Play_game
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1300, 800);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            this->Controls->Add(this->pictureBox1); 
            this->Controls->Add(this->buttonExit);
            this->Controls->Add(this->buttonStatus);
            this->Controls->Add(this->buttonBackpack);

            this->Name = L"Play_game";
            this->Text = L"Игра";
            this->StartPosition = FormStartPosition::CenterScreen;
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        System::Void buttonExit_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (MessageBox::Show("Вы уверены, что хотите выйти из игры?", "Подтверждение",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
            {
                this->Close();
            }
        }

        System::Void buttonStatus_Click(System::Object^ sender, System::EventArgs^ e)
        {
            HideAllPanels();
            panelStatus->Visible = true;
            panelStatus->BringToFront();
            buttonCloseStatus->BringToFront();
            buttonExit->BringToFront();
            buttonStatus->BringToFront();
            buttonBackpack->BringToFront();
        }

        System::Void buttonBackpack_Click(System::Object^ sender, System::EventArgs^ e)
        {
            HideAllPanels();
            panelBackpack->Visible = true;
            panelBackpack->BringToFront();
            buttonCloseBackpack->BringToFront();
            buttonExit->BringToFront();
            buttonStatus->BringToFront();
            buttonBackpack->BringToFront();
        }

        System::Void buttonCloseStatus_Click(System::Object^ sender, System::EventArgs^ e)
        {
            panelStatus->Visible = false;
        }

        System::Void buttonCloseBackpack_Click(System::Object^ sender, System::EventArgs^ e)
        {
            panelBackpack->Visible = false;
        }

        System::Void Form_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
        {
            int moveSpeed = 10;

            switch (e->KeyCode)
            {
            case Keys::W:
            case Keys::Up:
                playerDirection = Direction::Up;
                isMoving = true;
                MovePlayer(0, -moveSpeed);
                UpdatePlayerImage();
                break;
            case Keys::S:
            case Keys::Down:
                playerDirection = Direction::Down;
                isMoving = true;
                MovePlayer(0, moveSpeed);
                UpdatePlayerImage();
                break;
            case Keys::A:
            case Keys::Left:
                playerDirection = Direction::Left;
                isMoving = true;
                MovePlayer(-moveSpeed, 0);
                UpdatePlayerImage();
                break;
            case Keys::D:
            case Keys::Right:
                playerDirection = Direction::Right;
                isMoving = true;
                MovePlayer(moveSpeed, 0);
                UpdatePlayerImage();
                break;
            case Keys::Space: 
                if (tutorialStep >= 1) AttackEnemy();
                break;
            case Keys::E: 
                UsePickupIfAny();
                break;
            }
        }

        System::Void Form_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
        {
            isMoving = false;
            UpdatePlayerImage();
        }

        System::Void PlayerAnimTimer_Tick(System::Object^ sender, System::EventArgs^ e)
        {
            if (isMoving)
            {
                useRightStep = !useRightStep;
                UpdatePlayerImage();
            }
        }

        System::Void EnemyTimer_Tick(System::Object^ sender, System::EventArgs^ e)
        {
            // Двигаем всех врагов к игроку
                            for (int i = enemies->Count - 1; i >= 0; --i)
                {
                    GameCharacter^ echar = enemies[i];
                    PictureBox^ espr = enemySprites[i];

                    int deltaX = 0;
                    int deltaY = 0;
                    if (echar->X < playerCharacter->X) deltaX = 1; else if (echar->X > playerCharacter->X) deltaX = -1;
                    if (echar->Y < playerCharacter->Y) deltaY = 1; else if (echar->Y > playerCharacter->Y) deltaY = -1;
                    echar->Move(deltaX * 2, deltaY * 2);

                    // простое раздвижение, чтобы не перекрывались
                    for (int j = 0; j < enemies->Count; ++j)
                    {
                        if (j == i) continue;
                        int dx = echar->X - enemies[j]->X;
                        int dy = echar->Y - enemies[j]->Y;
                        int d2 = dx*dx + dy*dy;
                        if (d2 < 55*55)
                        {
                            if (dx == 0 && dy == 0) dx = 1;
                            echar->Move(dx > 0 ? 1 : -1, dy > 0 ? 1 : -1);
                        }
                    }

                    espr->Location = System::Drawing::Point(echar->X, echar->Y);
                }
        }

        System::Void SpawnTimer_Tick(System::Object^ sender, System::EventArgs^ e)
        {
            if (spawnedEnemiesCount >= totalEnemiesCap)
            {
                spawnTimer->Stop();
                return;
            }
            if (enemiesAlive < totalEnemiesToSpawn)
            {
                SpawnOneEnemy();
                if (spawnedEnemiesCount >= totalEnemiesCap) spawnTimer->Stop();
            }
            else if (enemiesAlive >= totalEnemiesToSpawn)
            {
                // Ждем пока освободится место
            }
        }


      void UpdateHealthUI()
        {
            labelHealthStatus->Text = "Здоровье: " + playerCharacter->Health + "%";
        }

        bool IsEnemyInFront(GameCharacter^ enemy)
        {
            int dx = enemy->X - playerCharacter->X;
            int dy = enemy->Y - playerCharacter->Y;
            switch (playerDirection)
            {
            case Direction::Up:
                return dy < 0 && System::Math::Abs(dx) <= 120; // перед игроком вверх
            case Direction::Down:
                return dy > 0 && System::Math::Abs(dx) <= 120;
            case Direction::Left:
                return dx < 0 && System::Math::Abs(dy) <= 120;
            case Direction::Right:
                return dx > 0 && System::Math::Abs(dy) <= 120;
            }
            return true;
        }

        void AttackEnemy()
        {
            // Показать спрайт атаки в зависимости от направления
            switch (playerDirection)
            {
            case Direction::Up:    if (attackUp) playerSprite->Image = attackUp; break;
            case Direction::Right: if (attackRight) playerSprite->Image = attackRight; break;
            case Direction::Down:  if (attackDown) playerSprite->Image = attackDown; break;
            case Direction::Left:  if (attackLeft) playerSprite->Image = attackLeft; break;
            }
            playerAttackTimer->Stop();
            playerAttackTimer->Start();

            if (!tutorialCompleted) return;
            int damage = baseDamage + (hasGun ? 10 : 0);

            // Бьем ближайшего врага в большем радиусе и в направлении взгляда
            const int maxRange = 140; // больше радиус
            int bestIdx = -1;
            int bestDist2 = 99999999;
            for (int i = 0; i < enemies->Count; ++i)
            {
                if (!IsEnemyInFront(enemies[i])) continue;
                int dx = enemies[i]->X - playerCharacter->X;
                int dy = enemies[i]->Y - playerCharacter->Y;
                int d2 = dx*dx + dy*dy;
                if (d2 < bestDist2 && d2 <= maxRange*maxRange)
                {
                    bestDist2 = d2;
                    bestIdx = i;
                }
            }
            if (bestIdx >= 0)
            {
                if (enemySprites[bestIdx]->Tag == nullptr)
                    enemySprites[bestIdx]->Tag = 60; // стартовое hp
                int hp = safe_cast<int>(enemySprites[bestIdx]->Tag);
                hp -= damage;
                enemySprites[bestIdx]->Tag = hp;

                // показать взрыв на враге на короткое время
                if (explosionImage != nullptr)
                {
                    enemySprites[bestIdx]->Image = explosionImage;
                    explosionSprites->Add(enemySprites[bestIdx]);
                    explosionTicks->Add(5); // ~5*60мс
                    explosionTimer->Start();
                }

                if (hp <= 0)
                {
                    pictureBox1->Controls->Remove(enemySprites[bestIdx]);
                    enemySprites->RemoveAt(bestIdx);
                    enemies->RemoveAt(bestIdx);
                    enemiesAlive--;
                    if (enemiesAlive <= 0 && tutorialCompleted)
                    {
                        MessageBox::Show("Победа! Все враги побеждены.", "Победа");
                    }
                }
            }
        }

        System::Void PlayerAttackTimer_Tick(System::Object^ sender, System::EventArgs^ e)
        {
            playerAttackTimer->Stop();
            UpdatePlayerImage();
        }

        void UsePickupIfAny()
        {
            for (int i = 0; i < backpackList->Items->Count; ++i)
            {
                String^ item = backpackList->Items[i]->ToString();
                if (item == "Зелье")
                {
                    backpackList->Items->RemoveAt(i);
                    playerCharacter->Health = System::Math::Min(100, playerCharacter->Health + 30);
                    UpdateHealthUI();
                    break;
                }
            }
        }

        System::Void Play_game_Resize(System::Object^ sender, System::EventArgs^ e)
        {
            if (tutorialPanel != nullptr && tutorialPanel->Visible)
            {
                tutorialPanel->Location = System::Drawing::Point((this->ClientSize.Width - tutorialPanel->Width)/2, (this->ClientSize.Height - tutorialPanel->Height)/2);
                tutorialNextButton->Location = System::Drawing::Point((tutorialPanel->Width - tutorialNextButton->Width)/2, 105);
            }
        }

        System::Void ExplosionTimer_Tick(System::Object^ sender, System::EventArgs^ e)
        {
            for (int i = explosionSprites->Count - 1; i >= 0; --i)
            {
                int t = explosionTicks[i] - 1;
                explosionTicks[i] = t;
                if (t <= 0)
                {
                    // restore enemy base image
                    if (enemyBaseImage != nullptr)
                        explosionSprites[i]->Image = enemyBaseImage;
                    explosionTicks->RemoveAt(i);
                    explosionSprites->RemoveAt(i);
                }
            }
            if (explosionSprites->Count == 0) explosionTimer->Stop();
        }
    };
} 