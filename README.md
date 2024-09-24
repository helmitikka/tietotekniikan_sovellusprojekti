# tietotekniikan_sovellusprojekti

<!-- Readme:n muokkaukseen apuja: https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/about-readmes -->

<!-- Badget osoitteesta: https://shields.io/badges -->
![Static Badge](https://img.shields.io/badge/Arduino-008083) ![GitHub License](https://img.shields.io/github/license/helmitikka/tietotekniikan_sovellusprojekti) ![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/helmitikka/tietotekniikan_sovellusprojekti/main.yml)

![Placeholder-kuva, josta mallia ottamalla ymmärrämme, kuinka kuvia lisätään Readme:n kautta.](/Dokumentit/Kuvat/Readme/placeholder.png)

# Speden Spelit

**Speden Spelit** on muistipeli, joka testaa pelaajan muistia ja reaktiotaitoja. Peli on toteutettu Arduino-mikrokontrollerilla ja se sisältää LED-valoja, nappeja sekä pistetilanteen näyttävät näytöt.

## Sisältö

- [Projekti](#projekti)
- [Asennus](#asennus)
- [Käyttö](#käyttö)
- [Projektirakenne](#projektirakenne)
- [Ominaisuudet](#ominaisuudet)
- [Repositoryn rakenne](#repositoryn-rakenne)
- [Lisenssi](#lisenssi)
- [Tekijät](#tekijät)

## Projekti

Tämä projekti on osa Oulun ammattikorkeakoulun "Tietotekniikan sovellusprojekti" -kurssia. **Speden Spelit** on fyysinen muistipeli, jossa pelaajan tulee painaa oikeita nappeja syttyvien LED-valojen mukaisessa järjestyksessä. Peli vaikeutuu jokaisen 10. kierroksen jälkeen nopeuttaen valojen syttymistä.

Peli alkaa, kun kahta reunimmaista nappia painetaan hetken ajan. Aluksi syttyy yksi LED-valo, jonka jälkeen pelaajan tulee painaa sitä vastaavaa nappia. Jokaisen kierroksen myötä LEDien määrä kasvaa. Jos pelaaja painaa väärää nappia tai ei paina mitään nappia annetussa ajassa, peli loppuu.

Peli tallentaa suurimman saavutetun pistemäärän (High Score), joka näkyy 7-segmenttinäytöllä. Peli menee virransäästötilaan, jos sitä ei käytetä hetkeen, ja sen voi herättää painamalla jotain nappia.

## Asennus

1. Tähän tulee asennusohjeet.
2. Asennusohjeissa voi olla useampi kohta.

## Käyttö

1. Pelin käynnistäminen: Peli käynnistyy, kun kahta reunimmaista nappia pidetään hetki alhaalla.
2. Pelimekaniikka: LEDit syttyvät tietyssä järjestyksessä ja pelaajan tulee painaa oikeita nappeja samassa järjestyksessä.
3. Vaikeutuminen: Joka 10:nnes kierros peli nopeutuu.
4. Pelin päättyminen: Jos pelaaja painaa väärää nappia tai ei paina nappia annetussa ajassa, peli päättyy.
5. Virransäästötila: Peli menee unitilaan, jos sitä ei käytetä hetkeen. Pelin voi herättää painamalla mitä tahansa nappia.
6. High Score: Peli tallentaa suurimman saavutetun pistemäärän.

## Projektirakenne

Projektissa on neljä moduulia
- **Buttons** - hallinnoi painikkeiden syöttöjä
- **Leds** - hallinnoi LEDien sytyttämistä
- **Display** - näyttää pelitulokset ja High Scoren 7-segmenttinäytöillä
- **GameLogic** - sisältää pelilogiikan, kuten pelin aloittamisen, tarkastukset ja vaikeutumisen.

## Repositoryn rakenne
- .github/workflow - työnkulku (automaattiset prosessit)
- Dokumentit/Kuvat - projektiin kuuluvat piirikaaviot ym.
- SpedenSpelit/ - Pelin lähdekoodi
- .gitignore - Lista tiedostoista ja kansioista, joita Git ei seuraa (esim. vscode-kansio)
- LICENSE - Projektin lisenssitiedosto
- README.md - tämä tiedosto

## Ominaisuudet

- 4 LED-valoa
- 4 painonappia
- Pelin nopeus kasvaa joka 10:nnes kierros.
- Pelin pistetilanne ja High Score 7-segmenttinäytöillä
- Virransäästötila
- Fyysinen peli rakennetaan joko pahvilaatikkoon tai 3D tulostettuun koteloon

## Lisenssi

Tämä projekti on lisensoitu GNU General Public License v3.0 -lisenssillä. Lisätietoja lisenssin ehdoista [täällä](/LICENSE)

## Tekijät

Tämän projektin toteuttivat Oulun ammattikorkeakoulun opiskelijat:
- Joonatan
- Juho
- Elin
