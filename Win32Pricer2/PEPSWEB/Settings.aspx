<%@ Page Title="Paramètres" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Settings.aspx.cs" Inherits="PEPSWEB.Settings" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h2><%: Title %></h2>
        <div style="float:left; width:550px">
            <asp:Label ID="vlrt" runat="server" Text="Valeur Liquidative d'Origine (€)"></asp:Label>
        </div>
        <div style="float: left; width:200px">    
            <asp:TextBox id="vlr" Text="1000" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="psoust" runat="server" Text="Durée période de souscription (ans)"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:TextBox id="psous"  Text="0.3" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="dconstst" runat="server" Text="Nombre de dates de constatation pendant la souscription"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:TextBox id="dconsts" Text="4" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="matt" runat="server" Text="Maturité du Produit (ans)"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:TextBox id="mat" Text="5" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="volt" runat="server" Text="Volatilité"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:TextBox id="vol" Text="0.3" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="zct" runat="server" Text="Taux ZC en €"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:TextBox id="zc" Text="0.3" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="dconstpt" runat="server" Text="Nombre de dates de constatation pendant le reste de durée de vie du produit"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:TextBox id="dconstp" Text="4" runat="server" />
        </div>
        <br><br>
        
        <div style="float:left; width:550px">
            <asp:Label ID="pdt" runat="server" Text="Pas de différentiation"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:TextBox id="pd" Text="4" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="mct" runat="server" Text="Nombre de tour de Montecarlo"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:TextBox id="mc" Text="1000" runat="server" />
        </div>
        <br><br>
  
</asp:Content>
