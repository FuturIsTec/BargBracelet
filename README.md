# BargBracelet - Smart Child Safety Bracelet with ESP8266 & Android App

## 📌 Overview
BargBracelet is a **smart child safety bracelet** that uses an **ESP8266 module** to communicate with an **Android app** over WebSocket. The system helps parents **locate their children, send alerts, and receive responses** using vibration, LED flashing, and button presses.

---

## 🚀 Features
✅ **Real-time communication** between the bracelet (ESP8266) and the Android app  
✅ **WebSocket server** for fast message exchange  
✅ **Call Alert System:** Parents can trigger a **vibration + LED flashing** on the bracelet  
✅ **Child Response Mechanism:** The child can press a **push button** on the bracelet to stop the vibration and send a response back to the app  
✅ **Timeout Notification:** If the child doesn't respond within **10 seconds**, the app receives an automatic notification  
✅ **Reactivation:** Parents can **re-trigger the vibration** if the child doesn’t respond  
✅ **Flashing LED Indicator:** The LED **flashes for 5 seconds** after the button is pressed  

---

## 📡 How It Works
1️⃣ **Parent scans QR Code** on the bracelet to connect the child’s device  
2️⃣ **Parent taps “Call” in the Android app** → The bracelet starts **vibrating** and the **LED flashes**  
3️⃣ **Child presses the bracelet button** → The motor stops, LED flashes for 5 seconds, and a **notification is sent back to the app**  
4️⃣ **If the child doesn’t respond in 10 seconds**, an automatic **alert is sent to the app**  
5️⃣ Parent can **re-trigger vibration** from the app if needed  

---

## 🔗 WebSocket Communication
| **Message**                 | **Sender**       | **Receiver**      | **Action** |
|-----------------------------|-----------------|------------------|------------|
| `"CALL"`                    | **Android App** | **ESP8266**      | Vibrate motor, start LED flashing |
| `"bracelet button clicked"` | **ESP8266**     | **Android App**  | Stop vibration, send confirmation |
| `"No response from bracelet"` | **ESP8266**     | **Android App**  | Timeout alert if no button press |

---

## 🛠️ Hardware Requirements
- **ESP8266 NodeMCU** (WiFi module)  
- **Push Button** (For child response)  
- **Vibration Motor** (For alerts)  
- **LED** (For flashing indicator)  
- **Android Device** (For the parent app)  

---

## 📜 Code Explanation
- **ESP8266 Code:**
  - Handles WebSocket communication  
  - Controls **motor activation & LED flashing**  
  - Reads **button input** and sends messages to the app  
  - **Timeout mechanism** to alert the parent if no response  
- **Android App:**
  - Connects to the ESP8266 WebSocket server  
  - Sends **"CALL"** to trigger bracelet vibration  
  - Receives **button press response** from the bracelet  
  - Sends **"vibrate again"** if needed  

---

## 📷 Screenshots & GIF Demo
_(Include a GIF of the system in action)_  

---

## 📂 Installation & Usage
1. **Upload the ESP8266 Code** to your NodeMCU  
2. **Run the Android App** (Connect to the ESP WiFi)  
3. **Test the Communication:**
   - Click "Call" → The bracelet vibrates  
   - Press the button → The app receives confirmation  
   - If no response, a timeout alert is triggered  

---

## 📌 Future Enhancements
🔹 Add **GPS tracking** for real-time location updates  
🔹 Integrate **battery level monitoring**  
🔹 Implement **custom vibration patterns** for different alerts  
🔹 Improve UI/UX for the Android app  

---

## 👨‍💻 Contributors
Developed by **[Your Name]** 🚀
