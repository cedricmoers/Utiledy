using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using GammaTableGenerator;

namespace GammaTableGenerator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void UnsignedIntegerValidationTextBox(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("[^0-9]+");

            e.Handled = regex.IsMatch(e.Text);
        }

        private void IntegerValidationTextBox(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("[^+-0-9]+");

            e.Handled = regex.IsMatch(e.Text);
        }

        private void FloatValidationTextBox(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex(@"[^0-9+-.]+");

            e.Handled = regex.IsMatch(e.Text);
        }

        private void MaxInputValueButtonClick(object sender, RoutedEventArgs e)
        {
            var btn = (Button)sender;
            int val = Int32.Parse((string)btn.Content);
            ((GammaTableGeneratorClass)DataContext).MaxInput = val;
        }

        private void MaxOutputValueButtonClick(object sender, RoutedEventArgs e)
        {
            var btn = (Button)sender;
            int val = Int32.Parse((string)btn.Content);
            ((GammaTableGeneratorClass)DataContext).MaxOutput = val;
        }

        private void NumbersPerRowButtonClick(object sender, RoutedEventArgs e)
        {
            var btn = (Button)sender;
            int val = Int32.Parse((string)btn.Content);
            ((GammaTableGeneratorClass)DataContext).NumbersPerRow = val;
        }

    }
}
