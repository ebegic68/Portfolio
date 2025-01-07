import java.sql.*;
import java.util.Scanner;

public class registracija {
    private static final String URL = "jdbc:sqlite:registracija.db";

    public static void main(String[] args) {
        kreirajTabelu();
        try (Scanner procitaj = new Scanner(System.in)) {
            while (true) {
                System.out.println("\n SISTEM ZA REGISTRACIJU VOZILA \n");
                System.out.print("Unesite oznaku registarskih tablica (bez crtica): ");
                String unos = procitaj.nextLine();
                if (unos.toLowerCase().equals("exit")) {
                    System.out.println("Program se zatvaraa...");
                    break;
                }
                if (unos.contains("-")) {
                    System.out.println("Unos oznaka registacije se unose bez crtica. Pokusajte ponovo.");
                    continue;
                }
                if (!validirajFormat(unos)) {
                    System.out.println("Neispravan format. Pravilno je npr.: '123 A 456'. Pokusajte ponovo. ");
                    continue;
                }
                if (provjeriPostojanje(unos)) {
                    System.out.println("Broj registracije vec postoji. Unesite ponovo drugi broj.");
                } else {
                    dodajUBazu(unos);
                    System.out.println("Broj registracije je jedinstven i kreiran.");
                }
            }
        }
    }

    private static void kreirajTabelu() {
        try (Connection konekcija = DriverManager.getConnection(URL);
                Statement s = konekcija.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS  registracija (" + " id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    + "oznaka TEXT UNIQUE NOT NULL)";
            s.execute(sql);

        } catch (SQLException w) {
            w.printStackTrace();
        }
    }

    private static boolean validirajFormat(String unos) {
        return unos.matches("\\d{3} [A-Z] \\d{3}");
    }

    private static boolean provjeriPostojanje(String unos) {
        try (Connection konekcija = DriverManager.getConnection(URL);
                PreparedStatement p = konekcija.prepareStatement("SELECT COUNT(*) FROM registracija WHERE oznaka=?")) {
            p.setString(1, unos);
            ResultSet rez = p.executeQuery();
            rez.next();
            return rez.getInt(1) > 0;
        } catch (SQLException w) {
            w.printStackTrace();
            return false;
        }
    }

    private static void dodajUBazu(String unos) {
        try (Connection konekcija = DriverManager.getConnection(URL);
                PreparedStatement p = konekcija.prepareStatement("INSERT INTO registracija (oznaka) VALUES (?)")) {
            p.setString(1, unos);
            p.executeUpdate();
        } catch (SQLException w) {
            w.printStackTrace();
        }
    }
}