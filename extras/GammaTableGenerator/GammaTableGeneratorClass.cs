using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace GammaTableGenerator
{
    public class GammaTableGeneratorClass : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private float _gammaCorrectionFactor = 2.8f;
        public float GammaCorrectionFactor
        {
            get
            {
                return this._gammaCorrectionFactor;
            }
            set
            {
                if (value != this._gammaCorrectionFactor)
                {
                    this._gammaCorrectionFactor = value;
                    OnPropertyChanged();
                    OnPropertyChanged(nameof(TxtGammaCorrectionFactor));

                    Evaluate();
                }
            }
        }

        private int _maxInput = 4095;
        public int MaxInput
        {
            get
            {
                return this._maxInput;
            }
            set
            {
                if (value != this._maxInput)
                {
                    this._maxInput = value;
                    OnPropertyChanged();
                    OnPropertyChanged(nameof(TxtMaxInput));
                    Evaluate();
                }
            }
        }



        private int _maxOutput = 4095;
        public int MaxOutput
        {
            get
            {
                return this._maxOutput;
            }
            set
            {
                if (value != this._maxOutput)
                {
                    this._maxOutput = value;
                    OnPropertyChanged();
                    OnPropertyChanged(nameof(TxtMaxOutput));
                    Evaluate();
                }
            }
        }

        private int _numbersPerRow = 32;
        public int NumbersPerRow
        {
            get
            {
                return this._numbersPerRow;
            }
            set
            {
                if (value != this._numbersPerRow)
                {
                    this._numbersPerRow = value;
                    OnPropertyChanged();
                    OnPropertyChanged(nameof(OutputValuesAsCode));
                    OnPropertyChanged(nameof(TxtNumbersPerRow));
                }
            }
        }

        private int MaxOutputMaxDigits
        {
            get
            {
                return MaxOutput.ToString().Length;
            }
        }

        public string TxtMaxOutput
        {
            get
            {
                return this.MaxOutput.ToString();
            }
            set
            {
                if (UInt32.TryParse(value, out uint result))
                {
                    this.MaxOutput = (int) result;
                }
            }
        }

        public string TxtMaxInput
        {
            get
            {
                return this.MaxInput.ToString();
            }
            set
            {
                if (UInt32.TryParse(value, out uint result))
                {
                    this.MaxInput = (int) result;
                }
            }
        }

        public string TxtNumbersPerRow
        {
            get
            {
                return this.NumbersPerRow.ToString();
            }
            set
            {
                if (UInt32.TryParse(value, out uint result))
                {
                    this.NumbersPerRow = (int)result;
                }
            }
        }

        public string TxtGammaCorrectionFactor
        {
            get
            {
                return this.GammaCorrectionFactor.ToString();
            }
            set
            {
                if (float.TryParse(value, out float result))
                {
                    this.GammaCorrectionFactor = result;
                }
            }
        }


        private List<int> _outputValues = new List<int>();
        public List<int> OutputValues
        {
            get
            {
                return _outputValues;
            }
            set
            {
                if (value != this._outputValues)
                {
                    this._outputValues = value;
                    Evaluate();
                }
            }
        }

        public string OutputValuesAsCode
        {
            get
            {
                string str = "DATATYPE PROGMEM gamma[] = {";
                for (int i = 0; i < this.OutputValues.Count; i++)
                {
                    int value = this.OutputValues[i];

                    if (i > 0)
                        str += ",";
                    if ((i % this.NumbersPerRow) == 0)
                        str += "\r\n";

                    int valueDigits = value.ToString().Length;
                    for (int j = 0; j < MaxOutputMaxDigits - valueDigits; j++)
                    {
                        str += " ";
                    }

                    str += value.ToString();
                }

                str += " };\r\n";

                return str;

            }
        }

        public GammaTableGeneratorClass()
        {
            Evaluate();
        }

        private void Evaluate()
        {
            this.OutputValues.Clear();

            for (int i = 0; i <= MaxInput; i++)
            {
                int value = (int)(Math.Pow((float)i / (float)this.MaxInput, this.GammaCorrectionFactor) * this.MaxOutput + 0.5);

                this.OutputValues.Add(value);
            }

            OnPropertyChanged(nameof(OutputValuesAsCode));
            OnPropertyChanged(nameof(OutputValues));
        }

        private void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }


    }
}
