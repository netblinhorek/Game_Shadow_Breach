#pragma once

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for Registration
	/// </summary>
	public ref class Registration : public System::Windows::Forms::Form
	{
	public:
		Registration(void)
		{
			InitializeComponent();
			LoadBackgroundImage();
			baseClientSize = this->ClientSize;

			origBtnRegister = this->buttonRegister->Bounds;
			origBtnBack = this->buttonBack->Bounds;
			origLabelTitle = this->labelTitle->Bounds;
			origLabelName = this->labelName->Bounds;
			origLabelEmail = this->labelEmail->Bounds;
			origLabelPassword = this->labelPassword->Bounds;
			origTextBoxName = this->textBoxName->Bounds;
			origTextBoxEmail = this->textBoxEmail->Bounds;
			origTextBoxPassword = this->textBoxPassword->Bounds;

			this->Resize += gcnew EventHandler(this, &Registration::Registration_Resize);

			this->textBoxEmail->Leave += gcnew EventHandler(this, &Registration::CheckUserCredentials);
			this->textBoxPassword->Leave += gcnew EventHandler(this, &Registration::CheckUserCredentials);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Registration()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::Label^ labelTitle;
		System::Windows::Forms::Label^ labelName;
		System::Windows::Forms::Label^ labelEmail;
		System::Windows::Forms::Label^ labelPassword;
		System::Windows::Forms::TextBox^ textBoxName;
		System::Windows::Forms::TextBox^ textBoxEmail;
		System::Windows::Forms::TextBox^ textBoxPassword;
		System::Windows::Forms::Button^ buttonRegister;
		System::Windows::Forms::Button^ buttonBack;

		System::Drawing::Size baseClientSize;
		System::Drawing::Rectangle origBtnRegister;
		System::Drawing::Rectangle origBtnBack;
		System::Drawing::Rectangle origLabelTitle;
		System::Drawing::Rectangle origLabelName;
		System::Drawing::Rectangle origLabelEmail;
		System::Drawing::Rectangle origLabelPassword;
		System::Drawing::Rectangle origTextBoxName;
		System::Drawing::Rectangle origTextBoxEmail;
		System::Drawing::Rectangle origTextBoxPassword;

		void LoadBackgroundImage()
		{
			try
			{
				array<String^>^ possiblePaths = {
					"регистрация.gif",
				};

				bool imageLoaded = false;
				for each (String ^ path in possiblePaths)
				{
					if (System::IO::File::Exists(path))
					{
						pictureBox1->Image = Image::FromFile(path);
						pictureBox1->SizeMode = path->EndsWith(".gif", StringComparison::OrdinalIgnoreCase) ?
							PictureBoxSizeMode::Zoom : PictureBoxSizeMode::StretchImage;
						pictureBox1->Dock = DockStyle::Fill;
						imageLoaded = true;
						break;
					}
				}

				if (!imageLoaded)
				{
					pictureBox1->BackColor = Color::Black;
					MessageBox::Show("Фоновое изображение не найдено!\nПроверьте наличие файла 'регистрация.gif'", "Предупреждение",
						MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
			}
			catch (Exception^ ex)
			{
				pictureBox1->BackColor = Color::Black;
				MessageBox::Show("Ошибка загрузки изображения: " + ex->Message,
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		System::Void CheckUserCredentials(System::Object^ sender, System::EventArgs^ e)
		{
			String^ email = textBoxEmail->Text->Trim();
			String^ password = textBoxPassword->Text->Trim();

			if (email->Length > 0 && password->Length > 0)
			{
				String^ foundName = FindUserByNameAndPassword(email, password);
				if (foundName != nullptr)
				{
					textBoxName->Text = foundName;
					MessageBox::Show("Добро пожаловать назад, " + foundName + "!", "Автозаполнение",
						MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
		}

		String^ FindUserByNameAndPassword(String^ email, String^ password)
		{
			try
			{
				String^ csvPath = "visits.csv";
				if (File::Exists(csvPath))
				{
					array<String^>^ lines = File::ReadAllLines(csvPath);

					for (int i = 1; i < lines->Length; i++) 
					{
						if (lines[i]->Trim()->Length > 0)
						{
							array<String^>^ parts = lines[i]->Split(';');
							if (parts->Length >= 4) 
							{
								String^ storedEmail = parts[2]->Trim();
								String^ storedPassword = parts[3]->Trim();
								String^ storedName = parts[1]->Trim();

								if (String::Equals(storedEmail, email, StringComparison::OrdinalIgnoreCase) &&
									String::Equals(storedPassword, password))
								{
									return storedName;
								}
							}
						}
					}
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка чтения файла: " + ex->Message, "Ошибка",
					MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			return nullptr; 
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->labelTitle = (gcnew System::Windows::Forms::Label());
			this->labelName = (gcnew System::Windows::Forms::Label());
			this->labelEmail = (gcnew System::Windows::Forms::Label());
			this->labelPassword = (gcnew System::Windows::Forms::Label());
			this->textBoxName = (gcnew System::Windows::Forms::TextBox());
			this->textBoxEmail = (gcnew System::Windows::Forms::TextBox());
			this->textBoxPassword = (gcnew System::Windows::Forms::TextBox());
			this->buttonRegister = (gcnew System::Windows::Forms::Button());
			this->buttonBack = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();

			// pictureBox1
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1359, 793);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->BackColor = Color::Black;

			// labelTitle
			this->labelTitle->AutoSize = true;
			this->labelTitle->Font = gcnew System::Drawing::Font("Arial", 36, FontStyle::Bold);
			this->labelTitle->ForeColor = Color::White;
			this->labelTitle->BackColor = Color::Black;
			this->labelTitle->Text = "Регистрация";
			this->labelTitle->Location = Point(350, 100);
			this->labelTitle->BringToFront();

			// labelName
			this->labelName->AutoSize = true;
			this->labelName->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
			this->labelName->ForeColor = Color::White;
			this->labelName->BackColor = Color::Black;
			this->labelName->Text = "Имя:";
			this->labelName->Location = Point(400, 300);
			this->labelName->BringToFront();

			// textBoxName
			this->textBoxName->Font = gcnew System::Drawing::Font("Arial", 12);
			this->textBoxName->Location = Point(650, 300);
			this->textBoxName->Size = Drawing::Size(300, 30);
			this->textBoxName->BackColor = Color::White;
			this->textBoxName->ForeColor = Color::Black;
			this->textBoxName->BringToFront();

			// labelEmail
			this->labelEmail->AutoSize = true;
			this->labelEmail->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
			this->labelEmail->ForeColor = Color::White;
			this->labelEmail->BackColor = Color::Black;
			this->labelEmail->Text = "Почта:";
			this->labelEmail->Location = Point(400, 390);
			this->labelEmail->BringToFront();

			// textBoxEmail
			this->textBoxEmail->Font = gcnew System::Drawing::Font("Arial", 12);
			this->textBoxEmail->Location = Point(650, 390);
			this->textBoxEmail->Size = Drawing::Size(300, 30);
			this->textBoxEmail->BackColor = Color::White;
			this->textBoxEmail->ForeColor = Color::Black;
			this->textBoxEmail->BringToFront();

			// labelPassword
			this->labelPassword->AutoSize = true;
			this->labelPassword->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
			this->labelPassword->ForeColor = Color::White;
			this->labelPassword->BackColor = Color::Black;
			this->labelPassword->Text = "Пароль:";
			this->labelPassword->Location = Point(400, 480);
			this->labelPassword->BringToFront();

			// textBoxPassword
			this->textBoxPassword->Font = gcnew System::Drawing::Font("Arial", 12);
			this->textBoxPassword->Location = Point(650, 480);
			this->textBoxPassword->Size = Drawing::Size(300, 30);
			this->textBoxPassword->BackColor = Color::White;
			this->textBoxPassword->ForeColor = Color::Black;
			this->textBoxPassword->PasswordChar = '*';
			this->textBoxPassword->BringToFront();

			// buttonRegister
			this->buttonRegister->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
			this->buttonRegister->Location = Point(400, 570);
			this->buttonRegister->Size = Drawing::Size(550, 60);
			this->buttonRegister->Text = "Зарегистрироваться";
			this->buttonRegister->BackColor = Color::Black;
			this->buttonRegister->ForeColor = Color::White;
			this->buttonRegister->FlatStyle = FlatStyle::Flat;
			this->buttonRegister->Cursor = Cursors::Hand;
			this->buttonRegister->Click += gcnew System::EventHandler(this, &Registration::buttonRegister_Click);
			this->buttonRegister->BringToFront();

			// buttonBack
			this->buttonBack->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
			this->buttonBack->Location = Point(10, 20);
			this->buttonBack->Size = Drawing::Size(200, 60);
			this->buttonBack->Text = "Назад";
			this->buttonBack->BackColor = Color::Black;
			this->buttonBack->ForeColor = Color::White;
			this->buttonBack->FlatStyle = FlatStyle::Flat;
			this->buttonBack->Cursor = Cursors::Hand;
			this->buttonBack->Click += gcnew System::EventHandler(this, &Registration::buttonBack_Click);
			this->buttonBack->BringToFront();

			// Registration Form
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1359, 793);

			this->Controls->Add(this->labelTitle);
			this->Controls->Add(this->labelName);
			this->Controls->Add(this->labelEmail);
			this->Controls->Add(this->labelPassword);
			this->Controls->Add(this->textBoxName);
			this->Controls->Add(this->textBoxEmail);
			this->Controls->Add(this->textBoxPassword);
			this->Controls->Add(this->buttonRegister);
			this->Controls->Add(this->buttonBack);
			this->Controls->Add(this->pictureBox1);

			this->Name = L"Registration";
			this->Text = L"Регистрация - Вход";
			this->StartPosition = FormStartPosition::CenterScreen;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
		}

		System::Void buttonRegister_Click(System::Object^ sender, System::EventArgs^ e)
		{
			String^ name = textBoxName->Text->Trim();
			String^ email = textBoxEmail->Text->Trim();
			String^ password = textBoxPassword->Text->Trim();

			if (name->Length == 0 || email->Length == 0 || password->Length == 0)
			{
				MessageBox::Show("Пожалуйста, заполните все поля!", "Предупреждение",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			SaveToCSV(name, email, password);

			textBoxName->Text = "";
			textBoxEmail->Text = "";
			textBoxPassword->Text = "";

			this->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Close();
		}

		bool IsEmailAlreadyExists(String^ email)
		{
			try
			{
				String^ csvPath = "visits.csv";
				if (File::Exists(csvPath))
				{
					array<String^>^ lines = File::ReadAllLines(csvPath);

					for (int i = 1; i < lines->Length; i++) 
					{
						if (lines[i]->Trim()->Length > 0)
						{
							array<String^>^ parts = lines[i]->Split(';');
							if (parts->Length >= 3)
							{
								String^ storedEmail = parts[2]->Trim();
								if (String::Equals(storedEmail, email, StringComparison::OrdinalIgnoreCase))
								{
									return true;
								}
							}
						}
					}
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка проверки почты: " + ex->Message, "Ошибка",
					MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			return false;
		}

		void SaveToCSV(String^ name, String^ email, String^ password)
		{
			try
			{
				String^ csvPath = "visits.csv";
				array<String^>^ lines = {};
				int nextNumber = 1;

				if (System::IO::File::Exists(csvPath))
				{
					lines = System::IO::File::ReadAllLines(csvPath);
					for (int i = lines->Length - 1; i >= 0; i--)
					{
						if (lines[i]->Trim()->Length > 0 && !lines[i]->StartsWith("Номер"))
						{
							array<String^>^ parts = lines[i]->Split(';');
							if (parts->Length > 0)
							{
								int num;
								if (Int32::TryParse(parts[0], num))
								{
									nextNumber = num + 1;
									break;
								}
							}
						}
					}
				}

				String^ line = String::Format("{0};{1};{2};{3};{4};{5};{6};{7}",
					nextNumber, name, email, password, 0, 0, 0, 10);

				if (nextNumber == 1 && !System::IO::File::Exists(csvPath))
				{
					String^ header = "Номер;Имя;Почта;Пароль;Монеты;Зелье;Ключи;Урон";
					System::IO::File::WriteAllText(csvPath, header + Environment::NewLine + line + Environment::NewLine);
				}
				else
				{
					System::IO::File::AppendAllText(csvPath, line + Environment::NewLine);
				}

				MessageBox::Show("Данные успешно сохранены!", "Успех",
					MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка сохранения: " + ex->Message, "Ошибка",
					MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e)
		{
			this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->Close();
		}

		System::Void Registration_Resize(System::Object^ sender, System::EventArgs^ e)
		{
			if (baseClientSize.Width == 0 || baseClientSize.Height == 0) return;
			double sx = (double)this->ClientSize.Width / (double)baseClientSize.Width;
			double sy = (double)this->ClientSize.Height / (double)baseClientSize.Height;

			this->buttonRegister->Bounds = ScaleRect(origBtnRegister, sx, sy);
			this->buttonBack->Bounds = ScaleRect(origBtnBack, sx, sy);
			this->labelTitle->Bounds = ScaleRect(origLabelTitle, sx, sy);
			this->labelName->Bounds = ScaleRect(origLabelName, sx, sy);
			this->labelEmail->Bounds = ScaleRect(origLabelEmail, sx, sy);
			this->labelPassword->Bounds = ScaleRect(origLabelPassword, sx, sy);
			this->textBoxName->Bounds = ScaleRect(origTextBoxName, sx, sy);
			this->textBoxEmail->Bounds = ScaleRect(origTextBoxEmail, sx, sy);
			this->textBoxPassword->Bounds = ScaleRect(origTextBoxPassword, sx, sy);
		}

		System::Drawing::Rectangle ScaleRect(System::Drawing::Rectangle r, double sx, double sy)
		{
			return System::Drawing::Rectangle(
				(int)(r.X * sx), (int)(r.Y * sy), (int)(r.Width * sx), (int)(r.Height * sy)
			);
		}
#pragma endregion
	};
}