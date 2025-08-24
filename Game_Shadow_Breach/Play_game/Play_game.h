#pragma once

#include "Main.h"
namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Play_game
	/// </summary>
	public ref class Play_game : public System::Windows::Forms::Form
	{
	public:
		Play_game(void)
		{
			InitializeComponent();
			LoadBackgroundImage();
			InitializePanels();
			HideAllPanels(); // Скрыть все панели при запуске
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

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

		void LoadBackgroundImage()
		{
			try
			{
				String^ imagePath = "C:\\Users\\redmi\\Downloads\\загруженное (5).jpg";

				if (System::IO::File::Exists(imagePath))
				{
					pictureBox1->Image = Image::FromFile(imagePath);
					pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
				}
				else
				{
					MessageBox::Show("Файл изображения не найден: " + imagePath,
						"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка загрузки изображения: " + ex->Message,
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		void InitializePanels()
		{
			// Панель состояния персонажа (уже компактная)
			panelStatus = gcnew Panel();
			panelStatus->Size = System::Drawing::Size(300, 150);
			panelStatus->Location = System::Drawing::Point(300, 150);
			panelStatus->BackColor = Color::FromArgb(240, 240, 240);
			panelStatus->BorderStyle = BorderStyle::FixedSingle;
			panelStatus->Visible = false;

			// Кнопка закрытия панели состояния
			buttonCloseStatus = gcnew Button();
			buttonCloseStatus->Text = "X";
			buttonCloseStatus->Size = System::Drawing::Size(30, 30);
			buttonCloseStatus->Location = System::Drawing::Point(panelStatus->Width - 35, 5);
			buttonCloseStatus->BackColor = Color::LightCoral;
			buttonCloseStatus->ForeColor = Color::White;
			buttonCloseStatus->FlatStyle = FlatStyle::Flat;
			buttonCloseStatus->Click += gcnew EventHandler(this, &Play_game::buttonCloseStatus_Click);

			// Добавляем содержимое в панель состояния
			Label^ labelStatus = gcnew Label();
			labelStatus->Text = "Состояние персонажа:";
			labelStatus->Location = System::Drawing::Point(20, 20);
			labelStatus->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12, FontStyle::Bold);
			labelStatus->AutoSize = true;

			Label^ labelHealth = gcnew Label();
			labelHealth->Text = "Здоровье: 100%";
			labelHealth->Location = System::Drawing::Point(20, 60);
			labelHealth->AutoSize = true;

			Label^ labelMana = gcnew Label();
			labelMana->Text = "Мана: 100%";
			labelMana->Location = System::Drawing::Point(20, 90);
			labelMana->AutoSize = true;

			panelStatus->Controls->Add(buttonCloseStatus);
			panelStatus->Controls->Add(labelStatus);
			panelStatus->Controls->Add(labelHealth);
			panelStatus->Controls->Add(labelMana);

			// Панель рюкзака - УМЕНЬШЕННЫЙ РАЗМЕР
			panelBackpack = gcnew Panel();
			panelBackpack->Size = System::Drawing::Size(250, 200); // Уменьшил размер
			panelBackpack->Location = System::Drawing::Point(250, 100);
			panelBackpack->BackColor = Color::FromArgb(240, 240, 240);
			panelBackpack->BorderStyle = BorderStyle::FixedSingle;
			panelBackpack->Visible = false;

			// Кнопка закрытия панели рюкзака
			buttonCloseBackpack = gcnew Button();
			buttonCloseBackpack->Text = "X";
			buttonCloseBackpack->Size = System::Drawing::Size(25, 25); // Уменьшил кнопку
			buttonCloseBackpack->Location = System::Drawing::Point(panelBackpack->Width - 30, 5);
			buttonCloseBackpack->BackColor = Color::LightCoral;
			buttonCloseBackpack->ForeColor = Color::White;
			buttonCloseBackpack->FlatStyle = FlatStyle::Flat;
			buttonCloseBackpack->Click += gcnew EventHandler(this, &Play_game::buttonCloseBackpack_Click);

			// Добавляем содержимое в панель рюкзака - КОМПАКТНОЕ
			Label^ labelBackpack = gcnew Label();
			labelBackpack->Text = "Рюкзак:";
			labelBackpack->Location = System::Drawing::Point(10, 10);
			labelBackpack->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Bold); // Уменьшил шрифт
			labelBackpack->AutoSize = true;

			// Компактный список предметов
			ListBox^ listItems = gcnew ListBox();
			listItems->Location = System::Drawing::Point(10, 35);
			listItems->Size = System::Drawing::Size(220, 120); // Уменьшил размер
			listItems->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 9); // Уменьшил шрифт
			listItems->Items->Add("Меч");
			listItems->Items->Add("Щит");
			listItems->Items->Add("Зелье здоровья");
			listItems->Items->Add("Карта");

			panelBackpack->Controls->Add(buttonCloseBackpack);
			panelBackpack->Controls->Add(labelBackpack);
			panelBackpack->Controls->Add(listItems);

			// Добавляем панели на форму
			this->Controls->Add(panelStatus);
			this->Controls->Add(panelBackpack);
		}

		void HideAllPanels()
		{
			panelStatus->Visible = false;
			panelBackpack->Visible = false;
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

			// buttonExit (завершить)
			this->buttonExit->Location = System::Drawing::Point(0, 0);
			this->buttonExit->Name = L"buttonExit";
			this->buttonExit->Size = System::Drawing::Size(150, 50);
			this->buttonExit->TabIndex = 0;
			this->buttonExit->Text = L"завершить";
			this->buttonExit->UseVisualStyleBackColor = false;
			this->buttonExit->BackColor = System::Drawing::Color::LightGray;
			this->buttonExit->ForeColor = System::Drawing::Color::Black;
			this->buttonExit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold));
			this->buttonExit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonExit->FlatAppearance->BorderSize = 1;
			this->buttonExit->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
			this->buttonExit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonExit->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonExit->Click += gcnew System::EventHandler(this, &Play_game::buttonExit_Click);

			// buttonStatus (состояние персонажа)
			this->buttonStatus->Location = System::Drawing::Point(751, 0);
			this->buttonStatus->Name = L"buttonStatus";
			this->buttonStatus->Size = System::Drawing::Size(150, 50);
			this->buttonStatus->TabIndex = 1;
			this->buttonStatus->Text = L"состояние персонажа";
			this->buttonStatus->UseVisualStyleBackColor = false;
			this->buttonStatus->BackColor = System::Drawing::Color::LightGray;
			this->buttonStatus->ForeColor = System::Drawing::Color::Black;
			this->buttonStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, FontStyle::Bold));
			this->buttonStatus->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonStatus->FlatAppearance->BorderSize = 1;
			this->buttonStatus->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
			this->buttonStatus->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonStatus->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonStatus->Click += gcnew System::EventHandler(this, &Play_game::buttonStatus_Click);

			// buttonBackpack (рюкзак)
			this->buttonBackpack->Location = System::Drawing::Point(751, 791);
			this->buttonBackpack->Name = L"buttonBackpack";
			this->buttonBackpack->Size = System::Drawing::Size(150, 150);
			this->buttonBackpack->TabIndex = 3;
			this->buttonBackpack->Text = L"рюкзак";
			this->buttonBackpack->UseVisualStyleBackColor = false;
			this->buttonBackpack->BackColor = System::Drawing::Color::LightGray;
			this->buttonBackpack->ForeColor = System::Drawing::Color::Black;
			this->buttonBackpack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold));
			this->buttonBackpack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonBackpack->FlatAppearance->BorderSize = 1;
			this->buttonBackpack->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
			this->buttonBackpack->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonBackpack->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonBackpack->Click += gcnew System::EventHandler(this, &Play_game::buttonBackpack_Click);

			// pictureBox1
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1000, 800);
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;

			// Play_game
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(900, 1000);
			this->Controls->Add(this->buttonExit);
			this->Controls->Add(this->buttonStatus);
			this->Controls->Add(this->buttonBackpack);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Play_game";
			this->Text = L"Играть";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
		}
#pragma endregion

	private:
		System::Void buttonExit_Click(System::Object^ sender, System::EventArgs^ e)
		{
			this->Close();
		}

		System::Void buttonStatus_Click(System::Object^ sender, System::EventArgs^ e)
		{
			// Показать панель состояния, скрыть остальные
			HideAllPanels();
			panelStatus->Visible = true;
			panelStatus->BringToFront(); // Поверх других элементов
		}

		System::Void buttonBackpack_Click(System::Object^ sender, System::EventArgs^ e)
		{
			// Показать панель рюкзака, скрыть остальные
			HideAllPanels();
			panelBackpack->Visible = true;
			panelBackpack->BringToFront(); // Поверх других элементов
		}

		System::Void buttonCloseStatus_Click(System::Object^ sender, System::EventArgs^ e)
		{
			panelStatus->Visible = false;
		}

		System::Void buttonCloseBackpack_Click(System::Object^ sender, System::EventArgs^ e)
		{
			panelBackpack->Visible = false;
		}
	};
}