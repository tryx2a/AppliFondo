<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="PEPSWEB._Default" %>

<%@ Register Assembly="System.Web.DataVisualization, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35" Namespace="System.Web.UI.DataVisualization.Charting" TagPrefix="asp" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <link rel="stylesheet" href="//code.jquery.com/ui/1.11.4/themes/smoothness/jquery-ui.css">
    <script src="//code.jquery.com/jquery-1.10.2.js"></script>
    <script src="//code.jquery.com/ui/1.11.4/jquery-ui.js"></script>
    
        <br/>

        <div class="container">
            <div class="row">
                <div class="panel panel-default">
                    <div class="panel-heading">
                        <h3 class="panel-title">Couverture du produit</h3>
                    </div>
                    <div class="panel-body">
                        <div class="row">
                            <div class="col-sm-4">
                                Selectionner la date à couvrir : <br/>
                               <asp:TextBox id="datepicker" runat="server" />                  
                            </div>
                            <div class="col-sm-4">
                                <br />
                                <asp:CheckBox ID="CheckBox1" runat="server" Checked="true" Text="  Utiliser les données historiques"/>
                            </div>
                         </div>
                        <br /><br />
                        <div class="row">
                            <div class="col-sm-12">
                                <asp:Button ID="simul" runat="server" OnClick="simul_Click" Text="Simuler" />
                                 <br /><br />
                            </div>
                        </div>

                        <div class="row">
                            <div class="col-lg-12">
                                <asp:Label ID="sansRisque" runat="server">  </asp:Label>
                                <br /><br />
                                <asp:Label id="deltaV" rows="22" TextMode="multiline" runat="server" />
                                <br /><br />
                            </div>
                        </div>
                        <br><br>
                        
                    </div>
                </div>
             </div>
        </div>
  
    
    <script>
        $(function() {
            $("#MainContent_datepicker").datepicker({
                altField: "#MainContent_datepicker",
                closeText: 'Fermer',
                prevText: 'Précédent',
                nextText: 'Suivant',
                currentText: 'Aujourd\'hui',
                monthNames: ['Janvier', 'Février', 'Mars', 'Avril', 'Mai', 'Juin', 'Juillet', 'Août', 'Septembre', 'Octobre', 'Novembre', 'Décembre'],
                monthNamesShort: ['Janv.', 'Févr.', 'Mars', 'Avril', 'Mai', 'Juin', 'Juil.', 'Août', 'Sept.', 'Oct.', 'Nov.', 'Déc.'],
                dayNames: ['Dimanche', 'Lundi', 'Mardi', 'Mercredi', 'Jeudi', 'Vendredi', 'Samedi'],
                dayNamesShort: ['Dim.', 'Lun.', 'Mar.', 'Mer.', 'Jeu.', 'Ven.', 'Sam.'],
                dayNamesMin: ['D', 'L', 'M', 'M', 'J', 'V', 'S'],
                weekHeader: 'Sem.',
                dateFormat: 'dd/mm/yy',
                //Permet de saisir la date au moment de la selection
                onSelect: function () {
                    var day1 = $("#MainContent_datepicker").datepicker('getDate').getDate();
                    var month1 = $("#MainContent_datepicker").datepicker('getDate').getMonth() + 1;
                    var year1 = $("#MainContent_datepicker").datepicker('getDate').getFullYear();
                    var fullDate = day1 + "/" + month1 + "/" + year1;
                    currentDate = fullDate;
                    document.getElementById("MainContent_datepicker").value = currentDate;
                }
            });
        });
    </script>

</asp:Content>
