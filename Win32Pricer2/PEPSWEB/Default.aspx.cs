﻿using System;
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
            mainChart.Series["freeRiskInvested"].Points.Clear();
            for (int i = 0; i < payoff.Length; i++)
            {
                mainChart.Series["price"].Points.AddXY(i, payoff[i]);
                pr.Text += payoff[i].ToString() + " ; ";
            }
            for (int i = 0; i < portfolio.Length; i++)
            {
                mainChart.Series["portfolio"].Points.AddXY(i, portfolio[i]);
                intc.Text += portfolio[i].ToString() + " ; ";
            }
            
            for (int i = 0; i < partSansRisque.Length; i++)
            {
                mainChart.Series["freeRiskInvested"].Points.AddXY(i, partSansRisque[i]);
                couv.Text += partSansRisque[i].ToString()+" ; ";
            }
                



        }
    }
}