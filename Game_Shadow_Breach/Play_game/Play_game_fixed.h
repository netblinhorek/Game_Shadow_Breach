#pragma once

#include "Main.h"

namespace CppCLRWinFormsProject {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    // Класс для игрового персонажа
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

        // Игровые персонажи Character
        GameCharacter^ playerCharacter;
        GameCharacter^ enemyCharacter;

        // UI элементы интерфейса/панели
        System::Windows::Forms::Label^ labelHealthStatus;
        System::Windows::Forms::ListBox^ backpackList;
        System::Windows::Forms::Panel^ tutorialPanel;
        System::Windows::Forms::Label^ tutorialLabel;
        System::Windows::Forms::Button^ tutorialNextButton;

        // Переменные игры
        bool tutorialCompleted;
        int tutorialStep;
        bool hasGun;
        int baseDamage;
        int enemyHealth;
        System::Windows::Forms::Timer^ enemyTimer;
        System::Random^ rng;

        // Направления движения персонажа
        enum class Direction { Up, Right, Down, Left };
        Direction playerDirection;
        bool isMoving;
        bool useRightStep;
        Timer^ playerAnimTimer;

        // Спрайты анимации (idle и шаги)
        Bitmap^ idleUp;    Bitmap^ idleRight; Bitmap^ idleDown;  Bitmap^ idleLeft;
        Bitmap^ stepUpRight;    Bitmap^ stepUpLeft;
        Bitmap^ stepRightRight; Bitmap^ stepRightLeft;
        Bitmap^ stepDownRight;  Bitmap^ stepDownLeft;
        Bitmap^ stepLeftRight;  Bitmap^ stepLeftLeft;

    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        System::ComponentModel::Container^ components;

        void LoadBackgroundImage()
        {
            try
            {
                // Попытка загрузить фоновое изображение из разных путей
                array<String^>^ possiblePaths = {
                    "фон.png",
                    "backgrounds/фон.png",
                    "images/фон.png",
                    "../../Player_game/фон.png",
                    "C:\\Users\\redmi\\Pictures\\фон.png" // Абсолютный путь к изображению
                };

                bool imageLoaded = false;
                for each (String ^ path in possiblePaths)
                {
                    if (System::IO::File::Exists(path))
                    {
                        pictureBox1->Image = Image::FromFile(path);
                        pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
                        pictureBox1->Dock = DockStyle::Fill; // Растягиваем на весь экран
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
        
        // Загрузка изображений игрока
        void LoadPlayerImages()
        {
            // Стояние (idle)
            idleUp = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\W.jpg");
            idleRight = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\D.png");
            idleDown = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\S.png");
            idleLeft = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\A.png");

            // Шаги
            stepUpRight   = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\Шаг_правая_нога_W.png");
            stepUpLeft    = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\Шаг_левая_нога_W.png");
            stepRightRight= LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\Шаг_правая_нога_D.png");
            stepRightLeft = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\Шаг_левая_нога_D.png");
            stepDownRight = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\Шаг_правая_нога_S.png");
            stepDownLeft  = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\Шаг_левая_нога_S.png");
            stepLeftRight = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\Шаг_правая_нога_A.png");
            stepLeftLeft  = LoadBmpTransparentWhite("C:\\Game_Shadow_Breach\\Game_Shadow_Breach\\Main\\Шаг_левая_нога_A.png");
        }

        // Обновление изображения игрока
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

            // Анимация
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
            // Создание игрового персонажа
            playerCharacter = gcnew GameCharacter(400, 300, 100, 5.0f, "Player");

            // Создание спрайта игрока
            playerSprite = gcnew PictureBox();
            playerSprite->Size = System::Drawing::Size(50, 50);
            playerSprite->Location = System::Drawing::Point(playerCharacter->X, playerCharacter->Y);
            playerSprite->BackColor = Color::Transparent;
            playerSprite->BackgroundImage = nullptr;
            playerSprite->BackgroundImageLayout = ImageLayout::None;

            // Загрузка изображений
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

            // Таймер анимации игрока
            playerAnimTimer = gcnew Timer();
            playerAnimTimer->Interval = 150; // 150 миллисекунд между кадрами
            playerAnimTimer->Tick += gcnew EventHandler(this, &Play_game::PlayerAnimTimer_Tick);
            playerAnimTimer->Start();

            // Создание панели обучения
            tutorialPanel = gcnew Panel();
            tutorialPanel->Size = System::Drawing::Size(500, 120);
            tutorialPanel->Location = System::Drawing::Point(400, 10);
            tutorialPanel->BackColor = Color::FromArgb(200, 0, 0, 0);
            tutorialPanel->BorderStyle = BorderStyle::FixedSingle;
            tutorialLabel = gcnew Label();
            tutorialLabel->ForeColor = Color::White;
            tutorialLabel->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12, FontStyle::Bold);
            tutorialLabel->Location = System::Drawing::Point(10, 10);
            tutorialLabel->AutoSize = true;
            tutorialNextButton = gcnew Button();
            tutorialNextButton->Text = "Далее";
            tutorialNextButton->Location = System::Drawing::Point(400, 75);
            tutorialNextButton->Click += gcnew EventHandler(this, &Play_game::TutorialNext_Click);
            tutorialPanel->Controls->Add(tutorialLabel);
            tutorialPanel->Controls->Add(tutorialNextButton);
            this->Controls->Add(tutorialPanel);
            tutorialPanel->BringToFront();
            ShowTutorialStep();
        }

        void InitializeEnemy()
        {
            // Создание вражеского персонажа
            enemyCharacter = gcnew GameCharacter(600, 200, 80, 3.0f, "Enemy");

            // Создание спрайта врага
            enemySprite = gcnew PictureBox();
            enemySprite->Size = System::Drawing::Size(50, 50);
            enemySprite->Location = System::Drawing::Point(enemyCharacter->X, enemyCharacter->Y);
            enemySprite->BackColor = Color::Transparent;
            enemySprite->BackgroundImage = nullptr;
            enemySprite->BackgroundImageLayout = ImageLayout::None;

            // Загрузка изображения врага
            try
            {
                String^ enemyImagePath = "C:\\Users\\redmi\\Downloads\\508e97f6f953059896858b1a5b62985d.png";
                if (System::IO::File::Exists(enemyImagePath))
                {
                    Bitmap^ enemyImage = gcnew Bitmap(Image::FromFile(enemyImagePath));
                    enemyImage->MakeTransparent(Color::White); // Делаем белый цвет прозрачным

                    enemySprite->Image = enemyImage;
                    enemySprite->SizeMode = PictureBoxSizeMode::StretchImage;
                }
                else
                {
                    // Если изображение не найдено, создаем текстовую метку
                    enemySprite->BackColor = Color::Transparent;
                    Label^ enemyLabel = gcnew Label();
                    enemyLabel->Text = "E";
                    enemyLabel->Font = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
                    enemyLabel->ForeColor = Color::Red;
                    enemyLabel->BackColor = Color::Transparent;
                    enemyLabel->Dock = DockStyle::Fill;
                    enemyLabel->TextAlign = ContentAlignment::MiddleCenter;
                    enemySprite->Controls->Add(enemyLabel);
                }
            }
            catch (Exception^ ex)
            {
                // В случае ошибки также создаем текстовую метку
                enemySprite->BackColor = Color::Transparent;
                Label^ enemyLabel = gcnew Label();
                enemyLabel->Text = "E";
                enemyLabel->Font = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
                enemyLabel->ForeColor = Color::Red;
                enemyLabel->BackColor = Color::Transparent;
                enemyLabel->Dock = DockStyle::Fill;
                enemyLabel->TextAlign = ContentAlignment::MiddleCenter;
                enemySprite->Controls->Add(enemyLabel);
            }

            // Добавление спрайта на экран
            enemySprite->Parent = pictureBox1;
            pictureBox1->Controls->Add(enemySprite);
            enemySprite->BringToFront();

            // Создание таймера движения врага (закомментировано, чтобы не двигался)
            enemyTimer = gcnew Timer();
            enemyTimer->Interval = 100; // Обновление каждые 100 мс
            enemyTimer->Tick += gcnew EventHandler(this, &Play_game::EnemyTimer_Tick);
            // enemyTimer->Start(); // Закомментировано движение врага
        }

       void InitializePanels()
        {
            // Создание панели статуса
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

            // Создание панели рюкзака
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

            // Добавление панелей на форму
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
            // Обновление позиции персонажа
            playerCharacter->Move(deltaX, deltaY);

            // Обновление позиции спрайта
            playerSprite->Location = System::Drawing::Point(
                playerCharacter->X,
                playerCharacter->Y
            );
        }

        void MoveEnemyTowardsPlayer()
        {
            // Получение координат игрока и врага
            int playerX = playerCharacter->X;
            int playerY = playerCharacter->Y;
            int enemyX = enemyCharacter->X;
            int enemyY = enemyCharacter->Y;

            int deltaX = 0;
            int deltaY = 0;

            // Движение towards игрока
            if (enemyX < playerX) deltaX = 1;
            else if (enemyX > playerX) deltaX = -1;

            if (enemyY < playerY) deltaY = 1;
            else if (enemyY > playerY) deltaY = -1;

            // Обновление позиции врага
            enemyCharacter->Move(deltaX * 2, deltaY * 2); // Враг движется быстрее игрока

            // Обновление позиции спрайта врага
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

            // buttonExit (Выход)
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

            // buttonStatus (Статистика)
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

            // buttonBackpack (Рюкзак)
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

            // pictureBox1 - фон
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

            // Порядок: сначала фон, потом кнопки
            this->Controls->Add(this->pictureBox1); // Сначала фон
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
        }

        System::Void buttonBackpack_Click(System::Object^ sender, System::EventArgs^ e)
        {
            HideAllPanels();
            panelBackpack->Visible = true;
            panelBackpack->BringToFront();
        }

        System::Void buttonCloseStatus_Click(System::Object^ sender, System::EventArgs^ e)
        {
            panelStatus->Visible = false;
        }

        System::Void buttonCloseBackpack_Click(System::Object^ sender, System::EventArgs^ e)
        {
            panelBackpack->Visible = false;
        }

        // Обработка нажатий клавиш для движения персонажа
        System::Void Form_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
        {
            int moveSpeed = 10; // Скорость движения персонажа

            switch (e->KeyCode)
            {
            case Keys::W:
            case Keys::Up:
                playerDirection = Direction::Up;
                isMoving = true;
                MovePlayer(0, -moveSpeed);
                break;
            case Keys::S:
            case Keys::Down:
                playerDirection = Direction::Down;
                isMoving = true;
                MovePlayer(0, moveSpeed);
                break;
            case Keys::A:
            case Keys::Left:
                playerDirection = Direction::Left;
                isMoving = true;
                MovePlayer(-moveSpeed, 0);
                break;
            case Keys::D:
            case Keys::Right:
                playerDirection = Direction::Right;
                isMoving = true;
                MovePlayer(moveSpeed, 0);
                break;
            case Keys::Space: // Пробел для атаки
                AttackEnemy();
                break;
            case Keys::E: // E для использования
                UsePickupIfAny();
                break;
            }

            UpdatePlayerImage();
        }

        // Обработка отпускания клавиш для остановки анимации и перехода в idle состояние
        System::Void Form_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
        {
            isMoving = false;
            UpdatePlayerImage();
        }

        // Таймер анимации игрока
        System::Void PlayerAnimTimer_Tick(System::Object^ sender, System::EventArgs^ e)
        {
            if (isMoving)
            {
                useRightStep = !useRightStep;
                UpdatePlayerImage();
            }
        }

        // Таймер движения вражеского персонажа
        System::Void EnemyTimer_Tick(System::Object^ sender, System::EventArgs^ e)
        {
            MoveEnemyTowardsPlayer();
        }

        void ShowTutorialStep()
        {
            switch (tutorialStep)
            {
            case 0:
                tutorialLabel->Text = "Управление: WASD/стрелки для движения";
                break;
            case 1:
                tutorialLabel->Text = "Пробел для атаки врага (только после обучения)";
                break;
            case 2:
                tutorialLabel->Text = "Нажмите E для использования предметов";
                break;
            case 3:
                tutorialLabel->Text = "Другие кнопки: статистика, рюкзак, выход";
                break;
            case 4:
                tutorialLabel->Text = "Обучение завершено. Удачной игры!";
                tutorialCompleted = true;
                tutorialPanel->Visible = false;
                if (enemyTimer != nullptr) enemyTimer->Start();
                break;
            }
        }

        System::Void TutorialNext_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (tutorialStep < 4)
            {
                tutorialStep++;
                ShowTutorialStep();
            }
        }

        void UpdateHealthUI()
        {
            labelHealthStatus->Text = "Здоровье: " + playerCharacter->Health + "%";
        }

        void AttackEnemy()
        {
            if (!tutorialCompleted) return;
            int damage = baseDamage + (hasGun ? 10 : 0);
            enemyHealth -= damage;
            if (enemyHealth <= 0)
            {
                enemyHealth = 50;
                // Выпадение предметов
                int drop = rng->Next(0, 3); // 0 gun, 1 key, 2 potion
                if (drop == 0 && !hasGun)
                {
                    backpackList->Items->Add("Пистолет");
                    hasGun = true;
                }
                else if (drop == 1)
                {
                    backpackList->Items->Add("Ключ");
                }
                else
                {
                    backpackList->Items->Add("Зелье");
                }
            }
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
    };
} 