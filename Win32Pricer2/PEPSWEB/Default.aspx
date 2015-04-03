<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="PEPSWEB._Default" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <br><br>
    <asp:Button id="sim" Text="Simuler" ForeColor="White"  BorderStyle="Ridge" Font-Bold="true" Width="150" Height="40" runat="server" BackColor="Black" OnClick="sim_Click"/>
    <br><br>

    <div id="res" aria-hidden="true">
        <div style="float:left; width:550px">
            <asp:Label ID="prt" runat="server" Text="Prix: "></asp:Label>
        </div>
        <div style="float: left; width:200px">    
            <asp:TextBox id="pr" rows="10" TextMode="multiline" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="ict" runat="server" Text="Intervalle de Confiance: "></asp:Label>
        </div>
        <div style="float: left; width:300px">
            <asp:TextBox id="intc" rows="10" TextMode="multiline" runat="server" />
        </div>
        <br><br>

        <div style="float:left; width:550px">
            <asp:Label ID="couvt" runat="server" Text="Résultats de la couverture: "></asp:Label>
        </div>
        <div style="float: left; width:300px">
            <asp:TextBox id="couv" rows="10" TextMode="multiline" runat="server" />
        </div>
        <br><br>
    </div>
        

</asp:Content>
