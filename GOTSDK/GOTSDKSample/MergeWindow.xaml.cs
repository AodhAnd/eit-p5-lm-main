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
using GOTSDK.Position;
using System.Windows.Media.Media3D;

namespace GOTSDKSample
{
	/// <summary>
	/// Interaction logic for MergeWindow.xaml
	/// </summary>
	public partial class MergeWindow : Window
	{
		private Scenario3D targetScenario;
		private IEnumerable<Scenario> allScenarios;

		// This could use a numeric up/down control instead of this...
		public string TranslationX { get { return _translationX; } set { _translationX = value; TryUpdate(); } }
		private string _translationX = "0";

		public string TranslationY { get { return _translationY; } set { _translationY = value; TryUpdate(); } }
		private string _translationY = "0";

		public string TranslationZ { get { return _translationZ; } set { _translationZ = value; TryUpdate(); } }
		private string _translationZ = "0";

		public string RotationDegrees { get { return _rotationDegrees; } set { _rotationDegrees = value; TryUpdate(); } }
		private string _rotationDegrees = "0";

		public MergeWindow(Scenario3D target, IEnumerable<Scenario> allScenarios)
		{
			this.targetScenario = target;
			this.allScenarios = allScenarios;

			this._translationX = "" + (int)target.ScenarioTranslation.X;
			this._translationY = "" + (int)target.ScenarioTranslation.Y;
			this._translationZ = "" + (int)target.ScenarioTranslation.Z;
			this._rotationDegrees = "" + (int)target.ScenarioRotationAngle;

			InitializeComponent();

			this.DataContext = this;
		}

		private void TryUpdate()
		{
			int x, y, z, rotation;
			if (int.TryParse(TranslationX, out x) && int.TryParse(TranslationY, out y) && int.TryParse(TranslationZ, out z) && int.TryParse(RotationDegrees, out rotation))
			{
				this.targetScenario.ScenarioTranslation = new Vector3D(x, y, z);
				this.targetScenario.ScenarioRotationAngle = rotation;
			}
		}

		private void TextBox_PreviewTextInput(object sender, TextCompositionEventArgs e)
		{
			// Only allow numeric input
			e.Handled = !TextIsNumeric(e.Text);
		}

		private void Button_SetToMainScenario(object sender, RoutedEventArgs e)
		{
			// Set our new main scenario
			this.targetScenario.SetToMainScenario();

			// Make sure none of the other scenarios are main scenarios. 
			foreach (var other in this.allScenarios.Where(s => s != this.targetScenario))
				other.IsMainScenario = false;

			this.Close();
		}

		private static bool TextIsNumeric(string input)
		{
			if (string.IsNullOrWhiteSpace(input))
				return false;

			// Check if user is starting to enter a negative value
			if (input.Length == 1 && input[0] == '-')
				return true;

			int notUsed;
			return int.TryParse(input, out notUsed);
		}

		private void Button_Close(object sender, RoutedEventArgs e)
		{
			this.Close();
		}
	}
}
