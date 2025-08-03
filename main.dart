import ’dart:async’;
import ’dart:convert’;
import ’package:flutter/material.dart’;
import ’package:http/http.dart’ as http;
import ’package:shared_preferences/shared_preferences.dart’;
void main() async {
WidgetsFlutterBinding.ensureInitialized();
final themeMode = await getThemePreference();
runApp(MyApp(themeMode: themeMode));
}
class MyApp extends StatefulWidget {
final ThemeMode themeMode;
const MyApp({super.key, required this.themeMode});
@override
_MyAppState createState() => _MyAppState();
}
class _MyAppState extends State<MyApp> {
late ThemeMode _themeMode;
@override
void initState() {
super.initState();
_themeMode = widget.themeMode;
}
void toggleTheme(bool isDarkMode) async {
setState(() {
_themeMode = isDarkMode ? ThemeMode.dark : ThemeMode.light;
});
await saveThemePreference(_themeMode);
}
@override
Widget build(BuildContext context) {
return MaterialApp(
themeMode: _themeMode,
theme: ThemeData.light(),
darkTheme: ThemeData.dark(),
home: ParkingStatusScreen(
onThemeChanged: toggleTheme,
themeMode: _themeMode,
),
);
}
}
class ParkingStatusScreen extends StatefulWidget {
final Function(bool) onThemeChanged;
final ThemeMode themeMode;
const ParkingStatusScreen({
super.key,
required this.onThemeChanged,
required this.themeMode,
});
@override
_ParkingStatusScreenState createState() => _ParkingStatusScreenState();
}
class _ParkingStatusScreenState extends State<ParkingStatusScreen> {
final String authToken =
"VZ6xneKWbR_Od2OxUj2-8wEFKO8SBe1t"; // Replace with new token if needed
int availableSlots = 3;
List<int> slotStatus = [0, 0, 0];
@override
void initState() {
super.initState();
fetchData();
Timer.periodic(Duration(seconds: 3), (timer) => fetchData());
}
Future<void> fetchData() async {
try {
var response = await http.get(
Uri.parse(
"https://blynk.cloud/external/api/get?token=$authToken&V0&V1&V2&V3",
),
);
if (response.statusCode == 200) {
var data = json.decode(response.body);
setState(() {
slotStatus[0] = data["V0"] ?? 0;
slotStatus[1] = data["V1"] ?? 0;
slotStatus[2] = data["V2"] ?? 0;
availableSlots = data["V3"] ?? 3;
});
} else {
print("Failed to load data");
}
} catch (e) {
print("Error fetching data: $e");
}
}
@override
Widget build(BuildContext context) {
return Scaffold(
appBar: AppBar(
title: Text("Parking Slots Status"),
actions: [
Switch(
value: widget.themeMode == ThemeMode.dark,
onChanged: widget.onThemeChanged,
),
],
),
body: Column(
mainAxisAlignment: MainAxisAlignment.center,
children: [
Text(
"Available Slots: $availableSlots",
style: TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
),
SizedBox(height: 20),
GridView.builder(
shrinkWrap: true,
gridDelegate: SliverGridDelegateWithFixedCrossAxisCount(
crossAxisCount: 3,
childAspectRatio: 1.5,
),
itemCount: 3,
itemBuilder: (context, index) {
return Card(
color: slotStatus[index] == 1 ? Colors.red : Colors.green,
child: Center(
child: Text(
"Slot ${index + 1}\n${slotStatus[index] == 1 ? "Full" : "Empty"}",
textAlign: TextAlign.center,
style: TextStyle(color: Colors.white, fontSize: 18),
),
),
);
},
),
],
),
);
}
}
// Function to get stored theme preference
Future<ThemeMode> getThemePreference() async {
final prefs = await SharedPreferences.getInstance();
bool? isDarkMode = prefs.getBool(’isDarkMode’);
return isDarkMode == true ? ThemeMode.dark : ThemeMode.light;
}
// Function to save theme preference
Future<void> saveThemePreference(ThemeMode mode) async {
final prefs = await SharedPreferences.getInstance();
prefs.setBool(’isDarkMode’, mode == ThemeMode.dark);
}
