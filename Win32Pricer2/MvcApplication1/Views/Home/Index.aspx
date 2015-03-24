<%@ Page Language="C#" Inherits="System.Web.Mvc.ViewPage<dynamic>" %>

<!DOCTYPE html>

<html>
    <head runat="server">
    <meta name="viewport" content="width=device-width" />
    <title>Index</title>
    <link href="../../Content/bootstrap.css" rel="stylesheet" />
    
</head>
<body class="col-lg-12">
    <div class="page-header">
        <h1 class="alert alert-info">FONDO GARANTITO 2015</h1>
        <div>
            <form action="/Fondo" class="form-horizontal" method="post">

                <div class="panel panel-primary">
                    <div class="panel-heading">Données relatives au produit</div>
                    <div class="panel-body">

                        <div class="form-horizontal">

                            <div class="form-group">
                                <label class="col-sm-2 control-label">Valeur liquidative d'origine</label>
                                <div class="col-sm-10">
                                   <label class="col-sm-2 control-label">1000 €</label>
                                </div>
                            </div>

                            <div class="form-group">
                                <label class="col-sm-2 control-label">Durée de la période de souscription</label>
                                <div class="col-sm-10">
                                   <label class="col-sm-2 control-label">0.3 ans</label>
                                </div>
                            </div>

                            </div>

                            <div class="form-group">
                                <label class="col-sm-2 control-label">Nombre de dates de constatation pendant la souscription</label>
                                <div class="col-sm-10 col-lg-3">
                                  <input type="number" class="form-control">
                                </div>
                            </div>

                            <div class="form-group">
                                <label class="col-sm-2 control-label">Maturité du produit</label>
                                <div class="col-sm-10">
                                   <label class="col-sm-2 control-label">5 ans</label>
                                </div>
                            </div>

                            <div class="form-group">
                                <label class="col-sm-2 control-label">Volatilité</label>
                                <div class="col-sm-10">
                                   <label class="col-sm-2 control-label">NEANT</label>
                                </div>
                            </div>

                            <div class="form-group">
                                <label for="exampleInputFile" class="col-sm-2 control-label">Taux Zero-Coupon en euros</label>
                                <div class="col-sm-10 col-lg-3">
                                <input type="file" id="exampleInputFile">
                                </div>
                            </div>

                            <div class="form-group">
                                <label class="col-sm-2 control-label">Nombre de constatation pendant le reste de la durée de vie du produit</label>
                                <div class="col-sm-10">
                                   <label class="col-sm-2 control-label">1</label>
                                </div>
                            </div>

                            <div class="form-group">
                                <label class="col-sm-2 control-label">Nombre de rebalancement</label>
                                <div class="col-sm-10 col-lg-3">
                                  <input type="number" class="form-control">
                                </div>
                            </div>

                            <div class="form-group">
                                <label class="col-sm-2 control-label">Pas de différenciation</label>
                                <div class="col-sm-10">
                                   <label class="col-sm-2 control-label">0.1</label>
                                </div>
                            </div>

                            <div class="form-group">
                                <label class="col-sm-2 control-label">Nombre d'occurence dans la simulation de Monte Carlo</label>
                                <div class="col-sm-10 col-lg-3">
                                  <input type="number" class="form-control">
                                </div>
                            </div>

                        </div>
                    </div>
                </div>

                <!-- Composition du panier -->
                <div class="panel panel-primary" id="panel_panier">
                    <div class="panel-heading" >
                        <h4 class="panel-title">
                            <a data-toggle="collapse" data-parent="#panel_panier" href="#panier">Panier d'actifs </a>
                        </h4>
                    </div>
                    <div id="panier" class="panel-collapse collapse out">
                        <%=ViewData["Panier"] %>
                    </div>    
                </div>

                <input type="submit" value="Cliquer ici pour lancer les calculs" />
            </form>
        </div>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
    <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/js/bootstrap.min.js"></script>
</body>
</html>
