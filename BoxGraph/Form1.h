#pragma once
int i=0;
#include <boost/timer/timer.hpp>
#include <iostream>
#include <time.h>
#include <math.h>
#include <string>
#include <fstream>
#include <vector>
using namespace System::IO;
using namespace System::IO::Ports;
#define BOOST_THREAD_USE_DLL
boost::timer::cpu_timer timer,reached_end;
std::vector<double> xs,vals,cnts;
bool ready=false; // Is measurement value ready?
bool written=true; // Has the final measurement value for packet of pulses been written to textBox?
bool started=false; // Is measurement stared?
double BoxCarVal; // Measured value
long int Counter; // Number of pulses during last step
long int cumulative=0; // Number of pulses since the start of measurement;
int NUM_OF_PULSES=80; //Number of pulses per wavelength in a scan
const int PULSE_TIMEOUT=10; // Wait how long after last pulse train to detect the end of meaurement
namespace Escort {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	protected: 
	private: System::Windows::Forms::Timer^  timer1;
	private: System::IO::Ports::SerialPort^  BoxCar;




	private: System::Windows::Forms::Button^  RunButton;
	private: System::Windows::Forms::Button^  PauseButt;
	private: System::Windows::Forms::Button^  ResetButton;
	private: System::Windows::Forms::ComboBox^  BoxCarBox;




	private: System::Windows::Forms::Button^  ScanButton;
	private: System::Windows::Forms::Label^  label1;



	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Button^  ABut;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  PulseTB;

	private: System::Windows::Forms::Button^  PulseButt;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  NMBPLSLBL;
	private: System::Windows::Forms::ToolStripStatusLabel^  StanLBL;





	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->BoxCar = (gcnew System::IO::Ports::SerialPort(this->components));
			this->RunButton = (gcnew System::Windows::Forms::Button());
			this->PauseButt = (gcnew System::Windows::Forms::Button());
			this->ResetButton = (gcnew System::Windows::Forms::Button());
			this->BoxCarBox = (gcnew System::Windows::Forms::ComboBox());
			this->ScanButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->ABut = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->PulseTB = (gcnew System::Windows::Forms::TextBox());
			this->PulseButt = (gcnew System::Windows::Forms::Button());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->NMBPLSLBL = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->StanLBL = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea2->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea2);
			this->chart1->Location = System::Drawing::Point(264, 8);
			this->chart1->Name = L"chart1";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series3->Color = System::Drawing::Color::Red;
			series3->Name = L"cap";
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series4->Color = System::Drawing::Color::RoyalBlue;
			series4->Name = L"loss";
			series4->YAxisType = System::Windows::Forms::DataVisualization::Charting::AxisType::Secondary;
			this->chart1->Series->Add(series3);
			this->chart1->Series->Add(series4);
			this->chart1->Size = System::Drawing::Size(912, 573);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &Form1::chart1_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 200;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// BoxCar
			// 
			this->BoxCar->BaudRate = 19200;
			this->BoxCar->PortName = L"COM17";
			this->BoxCar->StopBits = System::IO::Ports::StopBits::Two;
			this->BoxCar->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &Form1::BoxCar_DataReceived);
			// 
			// RunButton
			// 
			this->RunButton->Location = System::Drawing::Point(12, 12);
			this->RunButton->Name = L"RunButton";
			this->RunButton->Size = System::Drawing::Size(75, 23);
			this->RunButton->TabIndex = 1;
			this->RunButton->Text = L"Run";
			this->RunButton->UseVisualStyleBackColor = true;
			this->RunButton->Click += gcnew System::EventHandler(this, &Form1::RunButton_Click);
			// 
			// PauseButt
			// 
			this->PauseButt->Location = System::Drawing::Point(93, 12);
			this->PauseButt->Name = L"PauseButt";
			this->PauseButt->Size = System::Drawing::Size(75, 23);
			this->PauseButt->TabIndex = 2;
			this->PauseButt->Text = L"Pause";
			this->PauseButt->UseVisualStyleBackColor = true;
			this->PauseButt->Click += gcnew System::EventHandler(this, &Form1::PauseButt_Click);
			// 
			// ResetButton
			// 
			this->ResetButton->Location = System::Drawing::Point(174, 12);
			this->ResetButton->Name = L"ResetButton";
			this->ResetButton->Size = System::Drawing::Size(75, 23);
			this->ResetButton->TabIndex = 3;
			this->ResetButton->Text = L"Reset";
			this->ResetButton->UseVisualStyleBackColor = true;
			this->ResetButton->Click += gcnew System::EventHandler(this, &Form1::ResetButton_Click);
			// 
			// BoxCarBox
			// 
			this->BoxCarBox->FormattingEnabled = true;
			this->BoxCarBox->Location = System::Drawing::Point(12, 573);
			this->BoxCarBox->Name = L"BoxCarBox";
			this->BoxCarBox->Size = System::Drawing::Size(75, 21);
			this->BoxCarBox->TabIndex = 4;
			// 
			// ScanButton
			// 
			this->ScanButton->Location = System::Drawing::Point(12, 531);
			this->ScanButton->Name = L"ScanButton";
			this->ScanButton->Size = System::Drawing::Size(75, 23);
			this->ScanButton->TabIndex = 6;
			this->ScanButton->Text = L"Scan Ports";
			this->ScanButton->UseVisualStyleBackColor = true;
			this->ScanButton->Click += gcnew System::EventHandler(this, &Form1::ScanButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 557);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"BoxCar";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 41);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 10;
			this->button2->Text = L"Save";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// ABut
			// 
			this->ABut->Location = System::Drawing::Point(93, 531);
			this->ABut->Name = L"ABut";
			this->ABut->Size = System::Drawing::Size(75, 23);
			this->ABut->TabIndex = 9;
			this->ABut->Text = L"Assign";
			this->ABut->UseVisualStyleBackColor = true;
			this->ABut->Click += gcnew System::EventHandler(this, &Form1::ABut_Click);
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::Window;
			this->textBox1->Location = System::Drawing::Point(12, 69);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(236, 414);
			this->textBox1->TabIndex = 11;
			// 
			// PulseTB
			// 
			this->PulseTB->Location = System::Drawing::Point(24, 499);
			this->PulseTB->Name = L"PulseTB";
			this->PulseTB->Size = System::Drawing::Size(100, 20);
			this->PulseTB->TabIndex = 12;
			this->PulseTB->Text = L"80";
			// 
			// PulseButt
			// 
			this->PulseButt->Location = System::Drawing::Point(130, 496);
			this->PulseButt->Name = L"PulseButt";
			this->PulseButt->Size = System::Drawing::Size(75, 23);
			this->PulseButt->TabIndex = 13;
			this->PulseButt->Text = L"Set";
			this->PulseButt->UseVisualStyleBackColor = true;
			this->PulseButt->Click += gcnew System::EventHandler(this, &Form1::PulseButt_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->NMBPLSLBL, this->StanLBL});
			this->statusStrip1->Location = System::Drawing::Point(0, 604);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(1216, 22);
			this->statusStrip1->TabIndex = 14;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// NMBPLSLBL
			// 
			this->NMBPLSLBL->Name = L"NMBPLSLBL";
			this->NMBPLSLBL->Size = System::Drawing::Size(37, 17);
			this->NMBPLSLBL->Text = L"Pulses";
			// 
			// StanLBL
			// 
			this->StanLBL->Name = L"StanLBL";
			this->StanLBL->Size = System::Drawing::Size(25, 17);
			this->StanLBL->Text = L"N/A";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1216, 626);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->PulseButt);
			this->Controls->Add(this->PulseTB);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->ABut);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ScanButton);
			this->Controls->Add(this->BoxCarBox);
			this->Controls->Add(this->ResetButton);
			this->Controls->Add(this->PauseButt);
			this->Controls->Add(this->RunButton);
			this->Controls->Add(this->chart1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void chart1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

				 double x;
				 StanLBL->Text=i.ToString()+"Testujma";
				 BoxCar->Write("?1\r"); // Whats the value of analog input 1?
				 BoxCar->Write("?c\r"); // Whats the state of counter C2?/ Reset said counter;
				 if (!started&&Counter>0) {
					 started=true;
					 timer.stop();
					 timer.start();
					 reached_end.stop();
					 reached_end.start();// Reset timer counting from last pulse

				 }
				 if (started&&reached_end.elapsed().wall>PULSE_TIMEOUT*1e9) {
					 started=false;
					 timer1->Enabled=false;
					 textBox1->BackColor=Color::FromName("LimeGreen");
				 }
				 if (started) {
					 i++;
					 if (Counter>0) {
						 reached_end.stop();
						 reached_end.start();
					 }
					 boost::timer::cpu_timer tkrok;
					 while (!ready&&tkrok.elapsed().wall<5e7){
					 }
					 if (ready) {
						 x=timer.elapsed().wall/1e9;
						 xs.push_back(x);
						 vals.push_back(BoxCarVal);
						 cnts.push_back(Counter);
						 if (i%10==0){
							 this->chart1->Series[0]->Points->AddXY(x,BoxCarVal);
							 this->chart1->Series[1]->Points->AddXY(x,Counter);
						 }
						 ready=false;
					 }


					 std::cout<<x<<" "<<timer.elapsed().wall/1e9<<std::endl;
				 }
			 }

	private: System::Void RunButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 ABut->Enabled=false;
				 this->NMBPLSLBL->Text=NUM_OF_PULSES.ToString()+" pulses/point";
				 BoxCar->NewLine="\r";
				 BoxCar->Open();
				 std::cout<<"Ports are open"<<std::endl;
				 BoxCar->Write("W0\r"); // Set delay to 0
				 BoxCar->Write("C\r"); // Set digital 2 as input and make it a counter;
				 BoxCar->Write("?c\r"); //Read the value of counter and reset it;
				 BoxCar->ReadLine(); // Discard the cvounter value;
				 this->timer1->Enabled=true;
				 
				 timer.start();
			 }
	private: System::Void ResetButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->chart1->Series[0]->Points->Clear();
				 this->chart1->Series[1]->Points->Clear();
			 }
	private: System::Void ScanButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 for each (String^ s in System::IO::Ports::SerialPort::GetPortNames()) 
				 {
					 this->BoxCarBox->Items->Add(s);
				 } 
			 }
	private: System::Void BoxCar_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {
				 double value;
				 int counter;
				 String^ line=BoxCar->ReadLine();
				 Double::TryParse(line,value);
				 BoxCarVal=value;
				 line=BoxCar->ReadLine();
				 Int32::TryParse(line,counter);
				 Counter=counter;
				 cumulative+=counter;
				 if (counter!=0) written=false;
				 if (cumulative % NUM_OF_PULSES==0&&cumulative!=0&&!written)//Last point in a packet of pulses
				 {
					 textBox1->Text+=cumulative.ToString()+" "+BoxCarVal.ToString()+"\r\n"; 
					 written=true;
				 }
				 Console::WriteLine(line);
				 ready=true;
			 }
	private: System::Void PauseButt_Click(System::Object^  sender, System::EventArgs^  e) {
				 timer1->Enabled=!(timer1->Enabled);
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (saveFileDialog1->ShowDialog() == ::System::Windows::Forms::DialogResult::OK ){
					 StreamWriter^ sw = gcnew StreamWriter(saveFileDialog1->FileName+".dat");
					 int size=xs.size();//chart1->Series[0]->Points->Count;
					 for (i=0;i<size;i++){
						 sw->WriteLine(xs[i].ToString()+" "+vals[i].ToString()+" "+cnts[i].ToString());
						 //chart1->Series[0]->Points[i]->XValue.ToString()+" "+chart1->Series[0]->Points[i]->YValues[0].ToString()+" "+chart1->Series[1]->Points[i]->YValues[0].ToString());
					 }
					 sw->Close();
					 System::IO::StreamWriter^ swpnt=gcnew System::IO::StreamWriter(saveFileDialog1->FileName+"pnts.dat");
					 swpnt->Write(textBox1->Text);
					 swpnt->Close();

				 }
			 }
	private: System::Void ABut_Click(System::Object^  sender, System::EventArgs^  e) {
				 BoxCar->PortName=BoxCarBox->Text;
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 std::string BoxCarport, escortport;
				 std::ifstream inpfile("ports.cfg");
				 timer.stop();
				 if(inpfile>>BoxCarport){
					 BoxCarBox->Text=gcnew String(BoxCarport.c_str());
					 if (BoxCarBox->Text!="") BoxCar->PortName=BoxCarBox->Text;
				 }
			 }
	private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 System::IO::StreamWriter^ sw=gcnew System::IO::StreamWriter("ports.cfg");
				 sw->WriteLine(BoxCarBox->Text);
				 sw->Close();
				 BoxCar->Close();
			 }
	private: System::Void PulseButt_Click(System::Object^  sender, System::EventArgs^  e) {
Int32::TryParse(PulseTB->Text,NUM_OF_PULSES);
			 }
};
}

