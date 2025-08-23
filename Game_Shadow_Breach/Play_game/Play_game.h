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
			LoadBackgroundImage(); // Загружаем изображение при создании формы
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
		System::Windows::Forms::Button^ buttonGameField;
		System::Windows::Forms::Button^ buttonBackpack;
		System::Windows::Forms::PictureBox^ pictureBox1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

		// Метод для загрузки фонового изображения
		void LoadBackgroundImage()
		{
			try
			{
				String^ imagePath = "C:\\Users\\redmi\\Downloads\\загруженное (5).jpg";

				// Проверяем существование файла
				if (System::IO::File::Exists(imagePath))
				{
					// Загружаем изображение в PictureBox
					pictureBox1->Image = Image::FromFile(imagePath);
					pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage; // Растягиваем изображение
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

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonExit = (gcnew System::Windows::Forms::Button());
			this->buttonStatus = (gcnew System::Windows::Forms::Button());
			this->buttonGameField = (gcnew System::Windows::Forms::Button());
			this->buttonBackpack = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();

			// 
			// buttonExit (завершить) - ПРАВАЯ СТОРОНА
			// 
			this->buttonExit->Location = System::Drawing::Point(800, 50);
			this->buttonExit->Name = L"buttonExit";
			this->buttonExit->Size = System::Drawing::Size(150, 50);
			this->buttonExit->TabIndex = 0;
			this->buttonExit->Text = L"завершить";
			this->buttonExit->UseVisualStyleBackColor = false;
			this->buttonExit->BackColor = System::Drawing::Color::Black;
			this->buttonExit->ForeColor = System::Drawing::Color::White;
			this->buttonExit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold));
			this->buttonExit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonExit->FlatAppearance->BorderSize = 1;
			this->buttonExit->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
			this->buttonExit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonExit->Click += gcnew System::EventHandler(this, &Play_game::buttonExit_Click);

			// 
			// buttonStatus (состояние персонажа) - ПРАВАЯ СТОРОНА
			// 
			this->buttonStatus->Location = System::Drawing::Point(800, 120);
			this->buttonStatus->Name = L"buttonStatus";
			this->buttonStatus->Size = System::Drawing::Size(150, 50);
			this->buttonStatus->TabIndex = 1;
			this->buttonStatus->Text = L"состояние персонажа";
			this->buttonStatus->UseVisualStyleBackColor = false;
			this->buttonStatus->BackColor = System::Drawing::Color::Black;
			this->buttonStatus->ForeColor = System::Drawing::Color::White;
			this->buttonStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, FontStyle::Bold));
			this->buttonStatus->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonStatus->FlatAppearance->BorderSize = 1;
			this->buttonStatus->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
			this->buttonStatus->Cursor = System::Windows::Forms::Cursors::Hand;

			// 
			// buttonGameField (Игровое поле) - ПРАВАЯ СТОРОНА
			// 
			this->buttonGameField->Location = System::Drawing::Point(800, 190);
			this->buttonGameField->Name = L"buttonGameField";
			this->buttonGameField->Size = System::Drawing::Size(150, 50);
			this->buttonGameField->TabIndex = 2;
			this->buttonGameField->Text = L"Игровое поле";
			this->buttonGameField->UseVisualStyleBackColor = false;
			this->buttonGameField->BackColor = System::Drawing::Color::Black;
			this->buttonGameField->ForeColor = System::Drawing::Color::White;
			this->buttonGameField->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold));
			this->buttonGameField->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonGameField->FlatAppearance->BorderSize = 1;
			this->buttonGameField->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
			this->buttonGameField->Cursor = System::Windows::Forms::Cursors::Hand;

			// 
			// buttonBackpack (рюкзак) - ПРАВАЯ СТОРОНА
			// 
			this->buttonBackpack->Location = System::Drawing::Point(800, 260);
			this->buttonBackpack->Name = L"buttonBackpack";
			this->buttonBackpack->Size = System::Drawing::Size(150, 50);
			this->buttonBackpack->TabIndex = 3;
			this->buttonBackpack->Text = L"рюкзак";
			this->buttonBackpack->UseVisualStyleBackColor = false;
			this->buttonBackpack->BackColor = System::Drawing::Color::Black;
			this->buttonBackpack->ForeColor = System::Drawing::Color::White;
			this->buttonBackpack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, FontStyle::Bold));
			this->buttonBackpack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonBackpack->FlatAppearance->BorderSize = 1;
			this->buttonBackpack->FlatAppearance->BorderColor = System::Drawing::Color::Gray;
			this->buttonBackpack->Cursor = System::Windows::Forms::Cursors::Hand;

			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1000, 800);
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;

			// 
			// Play_game
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1000, 800);
			this->Controls->Add(this->buttonExit);
			this->Controls->Add(this->buttonStatus);
			this->Controls->Add(this->buttonGameField);
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
			// Закрываем текущую форму и возвращаемся в главное меню
			this->Close();
		}
	};
}