using MvcApplication1.Models;
using MvcApplication1.ServiceReference;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace MvcApplication1.Controllers
{
    public class HomeController : Controller
    {
        //
        // GET: /Home/

        public ActionResult Index()
        {
            Panier panier = new Panier();
            List<MvcApplication1.Models.Action> ListeAction = panier.getListAction();



            string[] l2 = { "BRK.A" };
           
            ServiceReference.DataHistoricalColumn[] hc = new ServiceReference.DataHistoricalColumn[1];
            hc[0] = DataHistoricalColumn.Close;

            DateTime debut = new DateTime(2010,1,1);
            DateTime fin = new DateTime(2010,12,21);

            ServiceReference.ActifServiceClient client = new ServiceReference.ActifServiceClient();
            
            Data resultRq = client.getActifHistorique(l2,hc,debut,fin);

            client.Close();

            int tailleRes = resultRq.Ds.Tables[0].Rows.Count;

            ViewData["Panier"] = "<table class=\"table\"><tr><th>Date</th><th>Prix</th></tr>";

            for (int i = 0; i < tailleRes; i++)
            {
                ViewData["Panier"] += "<tr><td>" + resultRq.Ds.Tables[0].Rows[i]["Date"] + "</td><td>" + resultRq.Ds.Tables[0].Rows[i]["Close"] + "</td></tr>";
            }

           

           /* ViewData["Panier"] = "<table class=\"table\"><tr><th>ISIN</th><th>Nom</th><th>Devise</th><th>Prix Spot</th></tr>";

                    foreach (MvcApplication1.Models.Action action in ListeAction)
                    {
                        ViewData["Panier"] += "<tr><td>"+  action.isin + "</td><td>" + action.nom + "</td><td>"+action.devise+"</td><td>" + action.prix + "</td></tr>";
                    } 
                    ViewData["Panier"] +="</table>";*/

            return View();
        }

        


    }
}
