﻿<%@ Page Title="Paramètres" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Settings.aspx.cs" Inherits="PEPSWEB.Settings" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h2><%: Title %></h2>
        <div style="float:left; width:550px">
            <asp:Label ID="vlrt" runat="server" Text="Valeur Liquidative d'Origine (€)"></asp:Label>
        </div>
        <div style="float: left; width:200px">    
             <asp:Label ID="vlr" runat="server" Text="1000"></asp:Label>
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="psoust" runat="server" Text="Durée période de souscription (ans)"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:Label ID="psous" runat="server" Text="0.3"></asp:Label>
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="dconstst" runat="server" Text="Nombre de dates de constatation pendant la souscription"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:TextBox id="dconsts" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="matt" runat="server" Text="Maturité du Produit (ans)"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:Label ID="mat" runat="server" Text="5"></asp:Label>
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="zct" runat="server" Text="Taux d'actualisation en €"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:Label ID="zc" runat="server" Text="Euribor"></asp:Label>
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="dconstpt" runat="server" Text="Nombre de dates de constatation pendant le reste de durée de vie du produit"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:Label ID="dconstp" runat="server" Text="1"></asp:Label>
        </div>
        <br><br>
        
        <div style="float:left; width:550px">
            <asp:Label ID="pdt" runat="server" Text="Pas de différentiation"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:Label ID="pd" runat="server" Text="0.1"></asp:Label>
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="Ht" runat="server" Text="Nombre de dates de rebalancement"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:TextBox id="H" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="mct" runat="server" Text="Nombre de tour de Montecarlo"></asp:Label>
        </div>
        <div style="float: left; width:200px">
            <asp:TextBox id="mc" runat="server" />
        </div>
        <br><br>

        
        <br><br>
            <asp:Button id="config" Text="Enregistrer la configuration" ForeColor="White"  BorderStyle="Ridge" Font-Bold="true" Width="300" Height="40" runat="server" BackColor="Black" OnClick="saveSettings"/>
        <br><br>


</asp:Content>
