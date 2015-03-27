using MvcApplication1.Models;
using MvcApplication1.ServiceReference;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
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

    }
}
