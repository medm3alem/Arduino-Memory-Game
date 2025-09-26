# 🔋 Bako Motors Battery SoC Monitor

## 📌 Contexte
Ce projet a été développé pour **Bako Motors** afin de surveiller en temps réel le **State of Charge (SoC)** d’une batterie.  
La communication se fait via le **bus CAN** (CAN High & CAN Low) en interrogeant le **BMS** (Battery Management System) avec des requêtes CAN spécifiques, puis en affichant le résultat sur un **écran OLED I2C SSD1306**.

![Vue d'ensemble du montage avec écran OLED affichant SoC = 1](path/to/image1.jpg)  
*Assemblage complet : Arduino UNO connecté à une breadboard avec boutons, LED, écran OLED I2C affichant "SoC 1", et connexions visibles.*

![Vue rapprochée des composants et connexions](path/to/image2.jpg)  
*Vue détaillée : Écran OLED SSD1306 affichant "SoC 1", 4 boutons poussoirs (rouge, jaune, bleu, noir), LED allumée (verte), et breadboard avec câblages.*

## ⚙️ Matériel utilisé
- 🟦 **Arduino UNO**  
- 📡 **Module MCP_CAN (MCP2515 + TJA1050)**  
- 🖥️ **Écran OLED I2C SSD1306 (128x64 pixels)**  
- 🔘 **4 boutons poussoirs** (optionnels pour interactions avancées)  
- 💡 **LED indicateurs** (pour feedback visuel)  
- 🔋 Batterie avec **BMS compatible CAN** (Bako Motors, ex. LiFePO4 60V 50Ah)  

## 🛠️ Fonctionnalités principales
- Envoi de **requêtes CAN** vers l’ID correspondant du BMS.  
- Réception et décodage des **réponses CAN** contenant l’état de charge (SoC).  
- Affichage du niveau de batterie en **%** sur l’écran OLED.  
- Intégration de boutons et LED pour une interface interactive (ex. navigation ou reset).  

## 📂 Organisation du code
Le code source se trouve dans [`CAN_OLED.ino`](CAN_OLED.ino).  
*(Note : Mise à jour pour utiliser Adafruit_SSD1306 au lieu de LiquidCrystal_I2C.)*

## 🔧 Dépendances
Ce projet utilise les bibliothèques Arduino suivantes :  

- [`mcp_can`](https://github.com/coryjfowler/MCP_CAN_lib) : pour la communication CAN avec le MCP2515  
- `Adafruit_GFX` et `Adafruit_SSD1306` : pour contrôler l’écran OLED via I2C  

### Installation
- Ouvrir l’IDE Arduino  
- Aller dans **Sketch → Include Library → Manage Libraries...**  
- Rechercher et installer :  
  - **MCP_CAN_lib** (par Cory J. Fowler)  
  - **Adafruit GFX Library**  
  - **Adafruit SSD1306**  

## 🚀 Utilisation
1. Connecter le module MCP_CAN à l’Arduino UNO (SPI : pins 10, 11, 12, 13).  
2. Relier **CAN_H** et **CAN_L** du MCP2515 au bus CAN de la batterie.  
3. Brancher l’écran OLED I2C (SDA → A4, SCL → A5 sur Arduino UNO, adresse I2C 0x3C).  
4. Connecter les boutons et LED aux pins appropriés (ex. boutons sur 2-5, LED sur 6-9).  
5. Charger et téléverser le code `CAN_OLED.ino` dans l’Arduino.  
6. Mettre sous tension la batterie → le SoC s’affiche sur l’écran OLED (ex. "SoC 1").  

## 👨‍💻 Auteur
Projet réalisé par **[Ton nom]**, pour **Bako Motors**, 2025.  

## 📜 Licence
Ce projet est distribué sous la licence [MIT](LICENSE).
