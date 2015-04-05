using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Wrapper2;

namespace PEPSWEB
{
    public partial class Validation : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void sim_Click(object sender, EventArgs e)
        {
            try
            {

                double prix, ic, pnl;

                int timeStepSub = Convert.ToInt32(HttpContext.Current.Application["timeStepSub"]);
                int H = Convert.ToInt32(HttpContext.Current.Application["H"]);
                int samples = Convert.ToInt32(HttpContext.Current.Application["TourMC"]);
                double MATURITY = 5.3;

                WrapperClass2 wc = new WrapperClass2(timeStepSub, H, samples);
                wc.computePnlWrapper();
                prix = wc.getPriceWrapper();
                ic = wc.getICWrapper();
                pnl = wc.getPnLWrapper();

                double[] payoff = wc.getPayoff();
                double[] portfolio = wc.getPfCouverture();
                double[] partSansRisque = wc.getPartSansRisque();

                values.Text = "<table class=\"table\"><tr><th>Temps (années)</th><th>Prix du produit (€)</th><th>Valeur du portefeuille de couverture (€)</th><th>Valeur investie au taux sans risque (€)</th></tr>";

                // On nettoie les points du Chart s'il en existe
                mainChart.Series["price"].Points.Clear();
                mainChart.Series["portfolio"].Points.Clear();
                double minportfolio = 2000;
                double maxportfolio = 0;
                double minprice = 2000;
                double maxprice = 0;
                //mainChart.Series["freeRiskInvested"].Points.Clear();
                for (int i = 0; i < payoff.Length; i++)
                {
                    // Calcul du Max et du Min, s'il est trouvé pour ce tour on les stocke en mémoire
                    if (payoff[i] > maxprice)
                        maxprice = payoff[i];
                    if (payoff[i] < minprice)
                        minprice = payoff[i];
                    if (portfolio[i] > maxportfolio)
                        maxportfolio = portfolio[i];
                    if (portfolio[i] < minportfolio)
                        minportfolio = portfolio[i];

                    // On ajoute le point aux Series du chart
                    double abs = (i) * MATURITY / H;
                    mainChart.Series["price"].Points.AddXY(abs, payoff[i]);
                    mainChart.Series["portfolio"].Points.AddXY(abs, portfolio[i]);

                    // Ajout au Tableau
                    values.Text += "<tr><td>" + abs.ToString(".##") + "</td><td>" + payoff[i].ToString(".##") + "</td><td>" + portfolio[i].ToString(".##") + "</td><td>" + partSansRisque[i].ToString(".##") + "</td></tr>";

                }

                // On définit le max et le min des des axes du chart
                if (minportfolio < minprice)
                {
                    mainChart.ChartAreas[0].AxisY.Minimum = Math.Floor(minportfolio);
                }
                else
                {
                    mainChart.ChartAreas[0].AxisY.Minimum = Math.Floor(minprice);
                }

                if (maxportfolio < maxprice)
                {
                    mainChart.ChartAreas[0].AxisY.Maximum = Math.Ceiling(maxprice);
                }
                else
                {
                    mainChart.ChartAreas[0].AxisY.Maximum = Math.Ceiling(maxportfolio);
                }

                mainChart.ChartAreas[0].AxisX.Maximum = MATURITY;
                mainChart.ChartAreas[0].AxisX.Minimum = 0;
                mainChart.ChartAreas[0].AxisX.Title = "Temps (années)";

                //On active la vision de la légende
                mainChart.Legends[0].Enabled = true;
            }
            catch (AccessViolationException ave)
            {
                MessageBox.Show("La simulation a échoué\n" + "Cause: " + ave.ToString());
            }
            

        }


    }
}