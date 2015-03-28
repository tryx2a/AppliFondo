using MvcApplication1.Models;
using MvcApplication1.ServiceReference;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using Wrapper2;


namespace MvcApplication1.Controllers.Fondo
{
    public class FondoController : Controller
    {
        //
        // GET: /Fondo/

        public ActionResult Index()
        {

            return View(new Models.Fondo());
        }



        [AcceptVerbs(HttpVerbs.Post)]
        private ActionResult View(Models.Fondo fondo)
        {
            double prix;
            double ic;
            double pnl=0;

            DateTime debut = new DateTime(2010, 1, 4);
            DateTime fin = new DateTime(2010, 1, 4);

            string[] l = { "BUD", "AAPL", "SAN", "3988.HK", "BRK.A", "0939.HK", "CHL", "ENI.MI", "XOM", "GSZ.PA", "1398.HK", "MC.PA",
                              "MSFT", "PTR", "SAN.PA", "SIE.DE", "TEF", "TOT", "UN", "WMT" };
            ServiceReference.ActifServiceClient client = new ServiceReference.ActifServiceClient();
            ServiceReference.DataHistoricalColumn[] hc = new ServiceReference.DataHistoricalColumn[1];
            hc[0] = DataHistoricalColumn.Close;
            Data resultRq = client.getActifHistorique(l, hc, debut, fin);
            client.Close();

            TauxDeChange fx = new TauxDeChange();
            double fxUsdEuro = fx.getFxUsdEur()[0];
            double fxCnyEuro = fx.getFxYuanEur()[0];


            double[] getSpot_ = new double[22];
            getSpot_[0] = fxUsdEuro;
            getSpot_[1] = fxCnyEuro;
            for (int i = 2; i < 22; i++)
            {
                getSpot_[i] = Convert.ToDouble(resultRq.Ds.Tables[0].Rows[i - 2]["Close"]);
            }


            int timeStepsSub_ = Convert.ToInt32(Request["timeStepSub"]);
            int H_ = Convert.ToInt32(Request["H"]);
            int sample_ = Convert.ToInt32(Request["sample"]);

  
            WrapperClass2 wc = new WrapperClass2(timeStepsSub_,H_,sample_);

            //for pour initialiser spot de wc
            for (int i = 0; i < getSpot_.Length; i++)
            {
                wc.setSpot(getSpot_[i],i);
            }

            //wc.computePriceWrapper2();
            wc.computePnlWrapper();

            prix = wc.getPriceWrapper();
            ic = wc.getICWrapper();
            pnl = wc.getPnLWrapper();

            //Récupération du payoff
            double[] payoff = wc.getPayoff();
            double[] portfolio = wc.getPfCouverture();
            double[] partSansRisque = wc.getPartSansRisque();

            ViewData["Couverture"] = "<table class=\"table\"><tr><th>Part du taux sans risque</th><th>Payoff</th><th>Portefeuille de Couverture</th><th>Tracking Error</th></tr>";

            for (int i = 0; i < payoff.Length; i++)
            {
                double trackingError = portfolio[i] - payoff[i];
                ViewData["Couverture"] += "<tr><td>" + partSansRisque[i] + "</td><td>" + payoff[i] + "</td><td>" + portfolio[i] + "</td><td>" + trackingError + "</td></tr>";
            }

            ViewData["Couverture"] += "</table>";

            ViewData["Prix"] = prix.ToString();
            ViewData["IC"] = ic.ToString();
            ViewData["PnL"] = pnl.ToString();

            return View();
        }

        /*

        private void LoadGraphData()
        {
            // Preparing Data Source For Chart Control

            DataColumn dc = new DataColumn("Month", typeof(string));
            DataColumn dc1 = new DataColumn("Qnty", typeof(int));
            dt.Columns.Add(dc);
            dt.Columns.Add(dc1);
            DataRow dr1 = dt.NewRow();
            dr1[0] = "January";
            dr1[1] = 8465;
            dt.Rows.Add(dr1);
            DataRow dr2 = dt.NewRow();
            dr2[0] = "February";
            dr2[1] = 9113;
            dt.Rows.Add(dr2);
            DataRow dr3 = dt.NewRow();
            dr3[0] = "March";
            dr3[1] = 18305;
            dt.Rows.Add(dr3);
            DataRow dr4 = dt.NewRow();
            dr4[0] = "April";
            dr4[1] = 23839;
            dt.Rows.Add(dr4);
            DataRow dr5 = dt.NewRow();
            dr5[0] = "May";
            dr5[1] = 11167;
            dt.Rows.Add(dr5);
            DataRow dr6 = dt.NewRow();
            dr6[0] = "June";
            dr6[1] = 8838;
            dt.Rows.Add(dr6);
            DataRow dr7 = dt.NewRow();
            dr7[0] = "July";
            dr7[1] = 10800;
            dt.Rows.Add(dr7);
            DataRow dr8 = dt.NewRow();
            dr8[0] = "August";
            dr8[1] = 12115;
            dt.Rows.Add(dr8);
            DataRow dr9 = dt.NewRow();
            dr9[0] = "September";
            dr9[1] = 7298;
            dt.Rows.Add(dr9);
            DataRow dr10 = dt.NewRow();
            dr10[0] = "October";
            dr10[1] = 13186;
            dt.Rows.Add(dr10);
            DataRow dr11 = dt.NewRow();
            dr11[0] = "November";
            dr11[1] = 10460;
            dt.Rows.Add(dr11);
            DataRow dr12 = dt.NewRow();
            dr12[0] = "December";
            dr12[1] = 9964;
            dt.Rows.Add(dr12);
        }
        */
    }
}
