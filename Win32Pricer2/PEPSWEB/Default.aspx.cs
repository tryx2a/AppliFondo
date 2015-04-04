using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Wrapper2;

namespace PEPSWEB
{
    public partial class _Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
       
        }

        protected void sim_Click(object sender, EventArgs e)
        {
            double prix, ic, pnl;

            WrapperClass2 wc = new WrapperClass2();
            wc.computePnlWrapper();
            prix = wc.getPriceWrapper();
            ic = wc.getICWrapper();
            pnl = wc.getPnLWrapper();

            double[] payoff = wc.getPayoff();
            double[] portfolio = wc.getPfCouverture();
            double[] partSansRisque = wc.getPartSansRisque();

            mainChart.Series["price"].Points.Clear();
            mainChart.Series["portfolio"].Points.Clear();
            double minportfolio=2000;
            double maxportfolio=0;
            double minprice=2000;
            double maxprice=0;
            //mainChart.Series["freeRiskInvested"].Points.Clear();
            for (int i = 0; i < payoff.Length; i++)
            {
                if (payoff[i] > maxprice)
                    maxprice = payoff[i];
                if (payoff[i] < minprice)
                    minprice = payoff[i];
                mainChart.Series["price"].Points.AddXY(i, payoff[i]);
                pr.Text += payoff[i].ToString() + " ; ";
            }
            for (int i = 0; i < portfolio.Length; i++)
            {
                if (portfolio[i] > maxportfolio)
                    maxportfolio = portfolio[i];
                if (portfolio[i] < minportfolio)
                    minportfolio = portfolio[i];
                mainChart.Series["portfolio"].Points.AddXY(i, portfolio[i]);
                intc.Text += portfolio[i].ToString() + " ; ";
            }
            
            for (int i = 0; i < partSansRisque.Length; i++)
            {
                //mainChart.Series["freeRiskInvested"].Points.AddXY(i, partSansRisque[i]);
                couv.Text += partSansRisque[i].ToString()+" ; ";
            }

            if (minportfolio < minprice)
            {
                mainChart.ChartAreas[0].AxisY.Minimum = minportfolio;
            }else {
                mainChart.ChartAreas[0].AxisY.Minimum =minprice;
            }

            if (maxportfolio < maxprice)
            {
                mainChart.ChartAreas[0].AxisY.Maximum = maxprice;
            }
            else
            {
                mainChart.ChartAreas[0].AxisY.Maximum = maxportfolio;
            }


        }
    }
}