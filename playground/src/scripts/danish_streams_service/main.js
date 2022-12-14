/*#########################################################################
#                                                                         #
#   Simple script for testing the scriptable service browser              #
#   by creating a simple static browser with some cool radio              #
#   streams. URLs shamelessly stolen from Cool-Streams.xml.               #
#                                                                         #
#   Copyright                                                             #
#   (C) 2007, 2008 Nikolaj Hald Nielsen  <nhnFreespirit@gmail.com>        #
#   (C)       2008 Peter ZHOU <peterzhoulei@gmail.com>                    #
#   (C)       2008 Mark Kretschmann <kretschmann@kde.org>                 #
#                                                                         #
#   This program is free software; you can redistribute it and/or modify  #
#   it under the terms of the GNU General Public License as published by  #
#   the Free Software Foundation; either version 2 of the License, or     #
#   (at your option) any later version.                                   #
#                                                                         #
#   This program is distributed in the hope that it will be useful,       #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#   GNU General Public License for more details.                          #
#                                                                         #
#   You should have received a copy of the GNU General Public License     #
#   along with this program; if not, write to the                         #
#   Free Software Foundation, Inc.,                                       #
#   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         #
##########################################################################*/

function Station( name, url, description )
{
    this.name = name;
    this.url = url;
    this.description = description;
}


categories = new Object;


var p4Desc = "P4 er den st??rste og mest aflyttede danske radiokanal med et mix af landsd??kkende og regionale programmer. Fra DRs 11 regioner f??lger P4 lytterne d??gnet rundt med et alsidigt udbud af moderne public service radio.<p>Fra DRs 11 regioner hj??lper vi dig igennem din dag med god musik; vi giver dig b??de de brede og de hurtige nyheder, og s?? kan vi hj??lpe dig p?? vej i trafikken.<p>P4 - n??rmest din egen radio.";


categories["Danmarks Radio"]= new Array (
    new Station( "P1", "http://wmscr1.dr.dk/e02ch01m?wmcontentbitrate=300000", "P1 er den moderne oplysningskanal med nyheder og samfundsstof, der skaber indsigt. Her s??ttes politik og hverdag til debat i interviews, analyser og reportager. P1 s??ger ??rsager og tendenser bag de aktuelle nyheder og s??tter begivenhederne i perspektiv.<p>Man beh??ver ikke sidde stille og lytte i timevis for at f?? noget ud af P1. Vi g??r grundigt til v??rks og kommer godt i dybden, men der er mulighed for at st?? af og p?? undervejs. Rigtig mange af P1s programmer kan downloades og h??res som podcasting - hvor du vil og n??r du vil." ),
    new Station( "P2", "http://wmscr1.dr.dk/e02ch02m?wmcontentbitrate=300000", "P2 er radiokanalen for dig som har musik og kultur som en vigtig del af dit liv, og som gerne vil opleve og f??lge med i alt det der sker.<p>P2 er for dig som elsker god musik, hvad enten den er klassisk, jazz, verdensmusik eller alt det sp??ndende ind imellem.<p>P?? P2 bliver du hver eftermiddag i P2 Plus opdateret p?? alt det der sker i kulturen lige nu: film, litteratur, musik, teater, kunst og det du ikke anede eksisterede. I P2s magasinprogrammer i weekenden kan du g?? mere i dybden med de dele af kulturen, der interesserer dig mest.<p>P2 kan du bruge b??de til fordybelse og som g??-til-og-fra-radio p?? din vej gennem dagen derhjemme eller p?? arbejdet, p?? pc'en, i bilen, i toget.." ),
    new Station( "P3", "http://wmscr1.dr.dk/e02ch03m?wmcontentbitrate=300000", "P3 er radiokanalen for moderne unge og voksne, der kan lide at blive udfordret - b??de musikalsk og indholdsm??ssigt.<p>Musikken p?? P3 er et alsidigt og varierende mix af ny sp??ndende musik, morgendagens stjerner, nutidens hits og banebrydende klassikere.<p>Journalistisk sender P3 b??de P3 Nyheder klokken hel og uddybende interviews morgen og eftermiddag, ofte med us??dvanlige vinkler p?? nutidige og aktuelle emner.<p>Satiren p?? P3 er ikke kun sjov og fis. P3s satire har vid og bid, og kradser i b??de aktuelle og klassiske emner som optager danskerne.<p>Sporten byder p?? intens og direkte d??kning af de store begivenheder i b??de ind- og udland, samtidig med at der informeres bredt om mange idr??tsgrene. " ),
    new Station( "P4 Bornholm", "http://wmscr1.dr.dk/e04ch08m?wmcontentbitrate=300000", p4Desc ),
    new Station( "P4 Fyn", "http://wmscr1.dr.dk/e04ch06m?wmcontentbitrate=300000", p4Desc ),
    new Station( "P4 K??benhavn", "http://wmscr1.dr.dk/e04ch09m?wmcontentbitrate=300000", p4Desc ),
    new Station( "P4 Midt & Vest", "http://wmscr1.dr.dk/e04ch02m?wmcontentbitrate=300000", p4Desc ),
    new Station( "P4 Nordjylland", "http://wmscr1.dr.dk/e04ch01m?wmcontentbitrate=300000", p4Desc ),
    new Station( "P4 Sj??lland", "http://wmscr1.dr.dk/e04ch07m?wmcontentbitrate=300000", p4Desc ),
    new Station( "P4 Syd", "http://wmscr1.dr.dk/e04ch05m?wmcontentbitrate=300000", p4Desc ),
    new Station( "P4 Trekanten", "http://wmscr1.dr.dk/e04ch04m?wmcontentbitrate=300000", p4Desc ),
    new Station( "P4 ??stjyllands Radio", "http://wmscr1.dr.dk/e04ch03m?wmcontentbitrate=300000", p4Desc ),
    new Station( "P5", "http://wmscr1.dr.dk/e06ch01m?wmcontentbitrate=300000", "P5 byder p?? folkek??re v??rter som Nis Boesdal, J??rgen de Mylius, Hans Otto Bisgaard, S??ren Dahl, Karlo Staunskj??r og Margaret Lindhardt.<p>Der er plads til b??de viser, dansktop, popul??rmusik og mulighed for at genh??re det bedste fra DR???s arkiver. Det sker i programmer som Dansktoppen, Gyldne Genh??r, Giro 413, Eldorado, Nis p?? DAB og Cafe Hack." ),
    new Station( "DR Allegro", "http://wmscr1.dr.dk/e06ch03m?wmcontentbitrate=300000", "P?? DR Allegro finder du velkendt og popul??r klassisk musik. Foruden orkestermusik, klavermusik og kendte operaarier finder du filmmusik, musicalmelodier og danske sange.<p>Danske komponister og danske musikere er ogs?? rigt repr??senteret p?? kanalen, som kan h??res p?? enhver pc verden over." ),
    new Station( "DR Barometer", "http://wmscr1.dr.dk/e02ch09m?wmcontentbitrate=300000", "DR Barometer - hangout for musikalske soulmates og postcentral for folk med noget p?? hjerte.<p>Med fokus p?? indierock, indietronica, alternativ country og elektronica pr??senterer kanalen en perler??kke af danske og internationale bands hentet fra universet omkring det legendariske radioprogram Det Elektriske Barometer p?? P3.<p>Kanalen spiller aktuelle Barometerhits blandet op med klassikere fra programmets 20 ??rige historie - alt sammen krydret med lytternes stemmer, ??nsker og tanker fra tankev??ggen, samt genudsendelser af nye og gamle Barometerudsendelser." ),
    new Station( "DR MGP", "http://wmscr1.dr.dk/e06ch09m?wmcontentbitrate=300000", "DR MGP er kanalen hvor du kan h??re alle sangene fra MGP - krydret med de andre sange som MGP stjernerne ogs?? har lavet. Mathias, Amalie, SEB, Nicolai og alle de andre p?? din egen MGP kanal." ),
    new Station( "DR Boogieradio", "http://wmscr1.dr.dk/e02ch07m?wmcontentbitrate=300000", "DR Boogieradio spiller alle de hits du kender fra Boogie p?? tv og net. S??de Sys Bjerre og Jeppe \"fingerslap\" Voldum er dine v??rter, og ligesom musikken kan du altid h??re dem lige her, 24 timer i d??gnet! Du kan ogs?? genh??re ugens aktuelle Boogieliste og de bedste interviews fra tv." ),
    new Station( "DR Country", "http://wmscr1.dr.dk/e06ch06m?wmcontentbitrate=300000", "DR Country er hjemsted for countrygenren i den klassiske forstand.<p>Genren fortolkes bredt p?? kanalen, s?? du finder eksempelvis ogs?? de relaterede genrer bluegrass, countryrock og singer/songwriters. DR Country indeholder en blanding af god ny country og genrens ??ldre klassikere. " ),
    new Station( "DR Dansktop", "http://wmscr1.dr.dk/e02ch11m?wmcontentbitrate=300000", "DR Dansktop er kanalen for alle dem, der holder af dansktopmusik.<p>Hele d??gnet sender DR Dansktop alle de bedste sange indenfor genren. Du kan h??re dansktopmusikken, som den lyder i dag, men ogs?? h??re ??ldre hits.<p>Selvom fire ud af fem sange p?? DR Dansktop er danske, kan du ogs?? h??re svensk og tysk musik. B??de nyere musik fra de to lande samt ??ldre numre, der har inspireret dansktoppens danske hits. " ),
    new Station( "DR Electronica", "http://wmscr1.dr.dk/e06ch10m?wmcontentbitrate=300000", "DR Electronica er for lyttere med ??bne ??rer, hang til elektroniske klange og rytmiske finurligheder. B??de feinschmeckere, nybegyndere og nysgerrige kan v??re med i dette mindre kluborienterede univers.<p>DR Electronica er h??ndplukkede danske og internationale produktioner, der g??r en forskel i dag og i fremtiden." ),
    new Station( "DR Evergreen", "http://wmscr1.dr.dk/e06ch07m?wmcontentbitrate=300000", "DR Evergreen er for alle - unge som ??ldre - med en fork??rlighed for den klassiske fortolkning af kendte popul??rmelodier - evergreens.<p>P?? kanalen finder du danske og udenlandske evergreens, prim??rt inden for easy listening-genren , ofte fremf??rt med sangsolist akkompagneret af orkester, strygere og kor. Nyere indspilninger med yngre kunstnere, som stilm??ssigt passer ind i kanalen, er ogs?? repr??senteret p?? DR Evergreen." ),
    new Station( "DR Folk", "http://wmscr1.dr.dk/e06ch11m?wmcontentbitrate=300000", "DR Folk er farverig og afvekslende musik, der sp??nder fra dansk og nordisk folkrock til songwriters og folkemusik fra de britiske ??er og Nordamerika.<p>DR Folk har sine r??dder i den vestlige folkemusik, og rummer hele den sp??ndende udvikling fra 60???erne revival til de helt aktuelle udgivelser." ),
    new Station( "DR Hiphop", "http://wmscr1.dr.dk/e02ch08m?wmcontentbitrate=300000", "DR Hip Hop spiller det bedste inden for genren - fra undergrund til mainstream. Med v??gten p?? det nyeste fra dansk og U.S. Hip Hop, holder vi dig konstant opdateret og supplerer med de st??rste klassikere gennem tiderne. Det hele blandet godt op med afstikkere til U.K., norden og resten af verden. Og s?? er det uden snak - kun det pureste Hip Hop...24/7!" ),
    new Station( "DR Hit", "http://wmscr1.dr.dk/e04ch10m?wmcontentbitrate=300000", "DR Hit er bl??d popmusik med masser af gode hits og nyheder p?? hele timer.<p>DR Hit - Soundtracket til en lidt bedre dag." ),
    new Station( "DR Jazz", "http://wmscr1.dr.dk/e02ch05m?wmcontentbitrate=300000", "DR Jazz er kanalen der kun sender jazzmusik - 24 timer i d??gnet p?? DAB-radio og net.<p>DR Jazz favner bredt. V??sentligste kriterium er kvalitet med det bedste fra alle jazzens genrer og perioder; og selvf??lgelig med s??rlig opm??rksomhed p?? den danske jazz og DR Big Band.<p>Det er i mikset af musikken, vi skiller os ud fra andre jazzkanaler. Vi spiller det, du gerne vil h??re, og s?? s??rger vi ogs?? for, at du bliver gl??delig overrasket og m??der nye kunstnere og konstellationer, du ikke vidste, at du kunne lide eller kendte i forvejen.<p>DR Jazz genudsender ogs?? jazzredaktionens udsendelser fra DR P2" ),
    new Station( "DR Klassisk", "http://wmscr1.dr.dk/e02ch06m?wmcontentbitrate=300000", "DR Klassisk p?? DAB, kabel og net er kanalen for den klassiske musikelsker.<p>DR Klassisk sender hele klassiske v??rker og hele koncerter - mest live-optagelser, nye eller fra arkivet. Musikken bliver kort og kompetent pr??senteret af vore faste v??rter.<p>P?? DR Klassisk har den klassiske musik sit fulde udfoldelsesrum og afbrydes ikke af nyheder eller taleindslag.<p>DR Klassisk er dagen igennem det klassiske alternativ til P2, men vi genudsender ogs?? de flotte aften koncerter fra P2 - bl.a. torsdagskoncerterne. En mulighed for at h??re eller genh??re.<p>DR Klassisk er den rene klassiske kanal p?? musikkens pr??misser." ),
    new Station( "DR Modern Rock", "http://wmscr2.dr.dk/e06ch02m?wmcontentbitrate=300000", "DR Modern Rock er kanalen for dig, hvis rockmusikken bare ikke kan blive nok udadvendt, tempofyldt, varieret, kantet, gr??nses??gende, dynamisk og gennemslagskraftig.<p>Kanalen favner b??de genrens nyeste, hotteste og mest aktuelle hits fra ind- og udland, men er ogs?? stedet hvor du m??der undergrundens myriader af unge, talentfulde - is??r danske - bands." ),
    new Station( "DR Nyheder", "http://wmscr2.dr.dk/e04ch11m?wmcontentbitrate=300000", "Lyt til nyheder, n??r du har lyst.  H??r de  seneste nyheder - opdateret hver time - d??gnet rundt. " ),
    new Station( "DR Oline", "http://wmscr1.dr.dk/e04ch12m?wmcontentbitrate=300000", "Oline er radio for b??rn mellem 3-7 ??r. Klokken 7.00 og kl. 18.30 er der nyt p?? Oline hver dag.<p>Oline indeholder masser af historier og det er alt fra gamle klassiske eventyr til b??rneb??ger der lige er udkommet.<p>Der er masser af b??rn der fort??ller om stor og sm?? ting i deres dagligdag - venskaber k??ledyr og den nye cykel Sofus fik i f??dselsdagsgave - og det er ogs?? p?? Oline du kan h??re Anna og Lotte, Sigurds Bj??rneradio og Kaj og Andrea i radioversionen.<p>Og s?? er der masser af musik for lige netop denne m??lgruppe p?? Oline. Her finder du den musik som er skrevet til b??rn - men ogs?? engang imellem musik som f??r en til at sp??rre ??rerne op og blive overrasket. " ),
    new Station( "DR P5000", "http://wmscr2.dr.dk/e06ch04m?wmcontentbitrate=300000", "P5000 er Mascha Vang, Anders Stjernholm og Anders Bonde. Blondinen, festaben og gammelsm??lfen er holdet fra helvede. Mixet med sladdernyt og musikken du elsker.<p>Fredag og l??rdag skruer vi ekstra op for festen, med top 25 p?? dancecharten plus to timer mixet af superstar-dj Morten Breum." ),
    new Station( "DR Pop DK", "http://wmscr1.dr.dk/e02ch10m?wmcontentbitrate=300000", "" ),
    new Station( "DR R&B", "http://wmscr1.dr.dk/e06ch08m?wmcontentbitrate=300000", "Er du til bl??de toner, s?? spiller DR R&B musik for dig, der er til R&B og soulmusik. Kanalen indeholder overvejende ny musik, hvilket betyder, at det er her, du kan lytte til de nye hits, og hvad der m??tte v??re p?? vej.<p>P?? kanalen kan du h??re flere nye numre fra nye udgivelser - og ikke kun ??n single ad gangen. DR R&B er ogs?? klassikere inden for genren og ??ldre soulhits. Det er ogs?? her, du kan tjekke specielle remixes, white labels og meget mere. " ),
    new Station( "DR Rock", "http://wmscr1.dr.dk/e02ch04m?wmcontentbitrate=300000", "DR Rock er rock uden stop - 24 timer i d??gnet p?? DAB og nettet.<p>DR Rock er en rendyrket rockkanal med fokus p?? den klassiske rock fra 60'erne til i dag. Musikken er et mix af de store klassikere til de bedste albumtracks.<p>DR Rock er kanalen for alle rockelskere. De forskellige genrer inden for den popul??re rock og med de kunstnere der har defineret og ??ndret rocken gennem tiderne." ),
    new Station( "DR Soft", "http://wmscr1.dr.dk/e06ch05m?wmcontentbitrate=300000", "DR Soft er til dig, der elsker en god popmelodi.<p>P?? DR Soft kan du b??de h??re de nyeste hits og de gode gamle popklassikere fra stjerner som Phil Collins, George Michael og Eurythmics.<p>25 procent af den spillede musik er dansk, og der er masser af variation p?? playlisten.<p>Skriv til redaktionen:<p>Att: DR Soft<br>DR Musik og Medier<br>DR Byen<br>Emil Holms Kanal 20<br>0999 K??benhavn C<br>Mail: dr-soft@dr.dk" ),
    new Station( "DR Spillemand", "http://wmscr1.dr.dk/e04ch11m?wmcontentbitrate=300000", "DR Spillemand er farverig dansk, nordisk og irsk/skotsk folkemusik som den lyder i dag - spillet og sunget af musikere, der tager afs??t i gamle traditioner.<p>R??dder, fornyelse og nysgerrighed er kerneordene for kanalen, som is??r fokuserer p?? akustisk, nordisk musik. " ),
    new Station( "DR World", "http://wmscr1.dr.dk/e06ch12m?wmcontentbitrate=300000", "DR World tilbyder som eneste danske radiokanal verdensmusik d??gnet rundt. Her kan du h??re det nyeste fra 'World Music Charts Europe' krydret med klassikerne fra alle verdensdele - det velkendte og det ukendte.<p>DR World afspejler storbykulturen og tager udgangspunkt i moderne fortolkning af traditionel musik fra hele kloden, inklusive den danske verdensmusikscene. Hovedparten af musikken, du h??rer her, er udgivet indenfor de seneste 10 ??r.<p>DR World er med dig - d??gnet rundt - verden rundt." )
);

categories["Diverse"]= new Array (
    new Station( "Radio 2", "http://dix.media.webpartner.dk/radio2-96", "" ),
    new Station( "The Voice", "http://dix.media.webpartner.dk/voice128", "" ),
    new Station( "Radio 100FM", "http://onair.100fmlive.dk/100fm_live.mp3", "" ),
    new Station( "Radio 100FM Soft", "http://onair.100fmlive.dk/soft_live.mp3", "" ),
    new Station( "Cool FM", "http://stream2.coolfm.dk:80/CoolFM128", "" ),
    new Station( "ANR Hit FM2", "mms://media.xstream.dk/Radio_Hit_FM", "" ),
    new Station( "ANR Guld FM", "mms://media.xstream.dk/Radio_Guld_FM", "" ),
    new Station( "Radio ABC", "mms://media.xstream.dk/Radio_ABC", "" ),
    new Station( "ABC Solo FM", "mms://media.xstream.dk/Radio_Solo_FM ", "" ),
    new Station( "Radio Alfa ??stjylland", "mms://media.xstream.dk/Radio_Alfa", "" ),
    new Station( "Radio Skive", "mms://media.xstream.dk/Radio_Skive", "" ),
    new Station( "Radio Mojn", "mms://media.xstream.dk/Radio_Mojn", "" ),
    new Station( "Radio 3", "mms://media.xstream.dk/Radio_3", "" ),
    new Station( "Radio Sydhavs??erne", "mms://media.xstream.dk/Radio_Sydhavsoerene", "" ),
    new Station( "NOVAfm", "mms://stream.ventelo.dk/FM5", "" )
);


function DanishStreamsService()
{
    Amarok.debug( "creating Danish Radio Streams service..." );
    ScriptableServiceScript.call( this, "Danish Radio Streams", 2, "List of free online radio stations from Denmark", "List of free online radio stations from Denmark", false );
    Amarok.debug( "done." );
}

function onPopulating( level, callbackData, filter )
{
    if ( level == 1 ) 
    {
        for( att in categories )
        {
            Amarok.debug ("att: " + att + ", " + categories[att].name)
           
            item = Amarok.StreamItem;
	    item.level = 1;
	    item.callbackData = att;
	    item.itemName = att;
	    item.playableUrl = "";
	    item.infoHtml = "";
	    script.insertItem( item );

        }
        script.donePopulating();

    }
    else if ( level == 0 ) 
    {
        Amarok.debug( " Populating station level..." );
	//add the station streams as leaf nodes

        var stationArray = categories[callbackData];

	for ( i = 0; i < stationArray.length; i++ )
	{
		item = Amarok.StreamItem;
		item.level = 0;
		item.callbackData = "";
		item.itemName = stationArray[i].name;
		item.playableUrl = stationArray[i].url;
		item.infoHtml = stationArray[i].description;
                item.artist = "Netradio";
		script.insertItem( item );
	}
	script.donePopulating();
    }
}

script = new DanishStreamsService();
script.populate.connect( onPopulating );
