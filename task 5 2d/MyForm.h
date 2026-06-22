#pragma once

namespace Yakunin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace std;

	vec2 Vc;
	vec2 V;
	vec2 Vc_work, V_work;
	mat3 T;
	mat3 initT;

	/// <summary>
	/// Ñâîäêà äëÿ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: äîáàâüòå êîä êîíñòðóêòîðà
			//
		}

	protected:
		/// <summary>
		/// Îñâîáîäèòü âñå èñïîëüçóåìûå ðåñóðñû.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	protected:


	private:
		/// <summary>
		/// Îáÿçàòåëüíàÿ ïåðåìåííàÿ êîíñòðóêòîðà.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Òðåáóåìûé ìåòîä äëÿ ïîääåðæêè êîíñòðóêòîðà — íå èçìåíÿéòå 
		/// ñîäåðæèìîå ýòîãî ìåòîäà ñ ïîìîùüþ ðåäàêòîðà êîäà.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->DefaultExt = L"txt";
			this->openFileDialog->Filter = L"Òåêñòîâûå ôàéëû (*.txt)|*.txt|Âñå ôàéëû (*.*)|*.*";
			this->openFileDialog->Title = L"Îòêðûòü ôàéë";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(155, 120);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: float left = 30, right = 100, top = 20, bottom = 50;
			 float minX = left, maxX;
			 float minY = top, maxY;
			 float Wcx = left, Wcy;
			 float Wx, Wy;

			 int numXsect = 5, numYsect = 5;





	private: System::Void rectCalc() {
		maxX = ClientRectangle.Width - right;
		maxY = ClientRectangle.Height - bottom;
		Wcy = maxY;
		Wx = maxX - left;
		Wy = maxY - top;
	}

	private:System::Void worldRectCalc() {
		Vc_work = normalize(T*vec3(Vc, 1.f));
		V_work = mat2(T) * V;
	}

	private: float f(float x) {
		return tan(x);
	}

	private: bool f_exists(float x, float delta) {
		return fabs(2.f * acos(cos(x)) - Math::PI) > delta;
	}
	
	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {

		Graphics^ g = e->Graphics;
		g->Clear(Color::Aquamarine);

		Pen^ rectPen = gcnew Pen(Color::Black, 2);
		g->DrawRectangle(rectPen, left, top, Wx, Wy);

		Pen^ gridPen = gcnew Pen(Color::Black, 1);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);


		//êîîðäèíàòíà¤ ñåòêà ïî îñè x
		float gridStep_x = Wx / numXsect;
		float grid_dX = V_work.x / numXsect;
		float tick_x = Vc_work.x;
		for (int i = 0; i <= numXsect; i++) {

			float tmpXCoord_d = Wcx + i * gridStep_x;
			float tmpXCoord_v = Wcx + i * gridStep_x;
			
			g->DrawLine(gridPen, tmpXCoord_v, Wcy, tmpXCoord_v, minY);

			if (i > 0 && i < numXsect)
				g->DrawString(tick_x.ToString("F1"), drawFont, drawBrush, tmpXCoord_d, Wcy);

			tick_x += grid_dX;
		}

		//êîîðäèíàòíà¤ ñåòêà ïî îñè y
		float gridStep_y = Wy / numYsect;
		float grid_dY = V_work.y / numYsect;
		float tick_y = Vc_work.y;
		for (int i = 0; i <= numYsect; i++) {
			
			float tmpYCoord_g = Wcy - i * gridStep_y;
			
			g->DrawLine(gridPen, Wcx, tmpYCoord_g, maxX, tmpYCoord_g);

			if (i > 0 && i < numYsect)
				g->DrawString(tick_y.ToString("F1"), drawFont, drawBrush, maxX, tmpYCoord_g);

			tick_y += grid_dY;
		}
		







		Pen^ pen = gcnew Pen(Color::Blue, 1);
		float deltaX = V_work.x / Wx;

		bool hasStart;

		vec2 start, end;
		float x, y;
		start.x = Wcx;
		x = Vc_work.x;
		hasStart = f_exists(x, deltaX);
		if (hasStart) {
			y = f(x);
			start.y = Wcy - (y - Vc_work.y) / V_work.y * Wy;
		}
				
		while (start.x < maxX) {
			
			vec2 end;
			bool hasEnd;
			float deltaY;
			float red, green, blue;
			end.x = start.x + 1.f;
			x += deltaX;
						
			hasEnd = f_exists(x, deltaX);
			if (hasEnd) {
				y = f(x);
				deltaY = (y - Vc_work.y) / V_work.y;
				end.y = Wcy - deltaY * Wy;
			}
						
			vec2 tmpEnd = end;
			bool visible = hasStart && hasEnd && clip(start, end, minX, minY, maxX, maxY);
			if (visible) {
				if (deltaY > 1.f) deltaY = 1.f;
				if (deltaY < 0.f) deltaY = 0.f;
				green = 510.f * deltaY;
				if (deltaY < 0.5f) {
					blue = 255.f - green;
					red = 0.f;
				}
				else {
					blue = 0.f;
					red = green - 255.f;
					green = 510.f - green;
				}
				pen->Color = Color::FromArgb(red, green, blue);
				g->DrawLine(pen, start.x, start.y, end.x, end.y);
			}
			start = tmpEnd;
			hasStart = hasEnd;
		}
	}
	
	private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) {
		rectCalc();
		Refresh();
	}
	
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		
		Vc = vec2(-2.f, -2.f);
		V = vec2(4.f, 4.f);

		initT = mat3(1.f);
		T = initT;

		rectCalc();
		worldRectCalc();
	}
	
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		
		float centerX = Vc_work.x + V_work.x / 2;
		float centerY = Vc_work.y + V_work.y / 2;

		switch (e->KeyCode)	{

		case Keys::A:
			T = translate(-V_work.x / Wx, 0.f) * T;
			break;

		case Keys::Z:
			T = translate(-centerX, -centerY) * T;
			T = scale(1.1) * T;
			T = translate(centerX, centerY) * T;
			break;





		case Keys::D:
			T = translate(V_work.x / Wx, 0.f) * T;
			break;
		case Keys::W:
			T = translate(0.f, -V_work.y / Wy) * T;
			break;
		case Keys::S:
			T = translate(0.f, V_work.y / Wy) * T;
			break;
		case Keys::X:
			T = translate(-centerX, -centerY) * T;
			T = scale(0.9) * T;
			T = translate(centerX, centerY) * T;
			break;
		case Keys::T:
			T = translate(-centerX, -centerY) * T;
			T = scale(1.f, 0.9) * T;
			T = translate(centerX, centerY) * T;
			break;
		case Keys::G:
			T = translate(-centerX, -centerY) * T;
			T = scale(1.f, 1.1) * T;
			T = translate(centerX, centerY) * T;
			break;
		case Keys::Y:
			T = translate(-centerX, -centerY) * T;
			T = scale(0.9, 1.f) * T;
			T = translate(centerX, centerY) * T;
			break;
		case Keys::H:
			T = translate(-centerX, -centerY) * T;
			T = scale(1.1, 1.f) * T;
			T = translate(centerX, centerY) * T;
			break;
		case Keys::O:
			numXsect++, numYsect++;
			break;
		case Keys::L:
			if (numXsect > 2) { numXsect--, numYsect--; }
			break;






















		case Keys::Escape:
			T = initT;
			break;

		default:
			break;
		}
		worldRectCalc();
		Refresh();
	}
	
};
}
