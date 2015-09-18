using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using GOTSDK;
using System.Collections.ObjectModel;
using GOTSDK.Position;
using System.ComponentModel;
using GOTSDK.Master;

namespace GOTSDKSample
{
	/// <summary>
	/// Interaction logic for CalibrationWindow.xaml
	/// </summary>
	public partial class CalibrationWindow : Window
	{
		public ObservableCollection<ReceiverViewModel> Receivers { get; private set; }
		
		/// <summary>
		/// The resulting scenario (if everything went well).
		/// </summary>
		public Scenario3D CalibratedScenario { get; private set; }

		private CalibratorTriangle calibrator;
		private bool isCalibrating = false;
		private IMaster master;

		public CalibrationWindow(IEnumerable<Receiver> receivers, CalibratorTriangle calibrator, IMaster master)
		{
			this.Receivers = new ObservableCollection<ReceiverViewModel>();
			this.calibrator = calibrator;
			this.master = master;

			InitializeComponent();

			this.DataContext = this;

			foreach (var receiver in receivers.OrderBy(r => r.GOTAddress))
				this.Receivers.Add(new ReceiverViewModel(receiver));
		}

		public void AddNewMeasurement(Measurement measurement)
		{
			// Update level reading for each receiver
			foreach (var receiver in this.Receivers)
				receiver.UpdateLevel(measurement.GetLevelForReceiver(receiver.GOTAddress));

			if (this.isCalibrating)
			{
				this.calibrator.AddMeasurement(measurement);

				double progress;
				if (this.calibrator.IsCalibrationFinished(out progress))
				{
					// Get the finished scenario and close this window.
					this.isCalibrating = false;
					this.CalibratedScenario = calibrator.CreateScenario();
					this.Close();
				}
				else
				{
					this.progressBar.Value = progress;
				}				
			}
		}

		private void Button_StartCalibrate(object sender, RoutedEventArgs e)
		{
			// Set the new temperature in Master
			this.master.SetSetup(100, this.sliderTemperature.Value, MasterRadioLevel.Mid);

			this.calibrator.ClearData();
			this.calibrator.SetTargetReceivers(this.Receivers.Where(r => r.IsSelected).Select(r => r.GOTAddress));

			this.isCalibrating = true;
			this.buttonStartCalibrating.IsEnabled = false;
		}

		public class ReceiverViewModel : INotifyPropertyChanged
		{
			public Receiver Receiver { get; private set; }
			public bool IsSelected { get; set; }
			public GOTAddress GOTAddress { get { return this.Receiver.GOTAddress; } }
			public string LevelText { get { return "Level: " + (this.levelHistory.Count == 0 ? 0 : (int)this.levelHistory.Average()); } }

			private const int LevelHistorySize = 10;
			private Queue<int> levelHistory = new Queue<int>();
			private int updateCounter = 0;

			public ReceiverViewModel(Receiver receiver)
			{
				this.Receiver = receiver;
				this.IsSelected = true;
			}

			public void UpdateLevel(int newLevel)
			{
				this.levelHistory.Enqueue(newLevel);

				while (levelHistory.Count > LevelHistorySize)
					levelHistory.Dequeue();

				// Skip updating all the time a new value is set, otherwise the UI will look too confusing with numbers changing too often.
				if (updateCounter++ > 5)
				{
					OnPropertyChanged("LevelText");
					updateCounter = 0;
				}
			}

			#region INotifyPropertyChanged Members

			public event PropertyChangedEventHandler PropertyChanged = delegate { };

			private void OnPropertyChanged(string propertyName)
			{
				this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
			}

			#endregion
		}
	}
}
