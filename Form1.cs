namespace ConsoleAplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            String username = usernameField.Text;
            String password = passwordField.Text;

            /*string path = "note1.txt";
            string text = "Hello World\nHello METANIT.COM";

            // полная перезапись файла 
            using (StreamWriter writer = new StreamWriter(path, false))
            {
                await writer.WriteLineAsync(text);
            }*/

            StreamWriter f = new StreamWriter("C:\\Users\\yanav\\source\\repos\\OIB_11\\data.txt", false);
            f.WriteLine(username);
            f.WriteLine(password);
            f.Close();

            this.Close();
        }
    }
}