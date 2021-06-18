package prolab23;

import java.sql.*;

/*
import com.sun.jdi.connect.spi.Connection;
import java.beans.Statement;
import java.sql.ResultSet;
import java.sql.DriverManager;
import java.sql.Statement;
 */
public class Mysql {

    private Connection con;
    private String kKullaniciAdi;
    private String kSifre;
    private boolean kOdendi = true;
    private boolean kAdmin;
    private boolean kPremium;
    private String gKullaniciAdi;
    private String gSifre;
    private String agKullaniciAdi;
    private String agSifre;
    private boolean gAdmin;
    private boolean alinmis;
    private int kayitVarMi;
    private int akayitVarMi;
    private String sanatciAdi;
    private String albumAdi;
    private boolean sanatciVarMi = true;
    private boolean albumVarMi = true;

    public boolean isAlbumVarMi() {
        return albumVarMi;
    }

    public String getSanatciAdi() {
        return sanatciAdi;
    }
    public boolean isSanatciVarMi() {
        return sanatciVarMi;
    }

    public int getAkayitVarMi() {
        return akayitVarMi;
    }
    public int getKayitVarMi() {
        return kayitVarMi;
    }

    public boolean isAlinmis() {
        return alinmis;
    }

    //boş
    public Mysql() {
    }
    //sarki ekleme
    public Mysql(String sarkiAdi, int sanatciID, String tarih, int albumID, String Tur, String sure) {
        try {
            Connection();
            int ahmet=0;
            String query = " insert into sarkilar (sarkiAdi, tarih, sanatciAdi,album,tur,sure,dinlenmeSayisi)"
                    + " values (?, ?, ?, ?, ?,?,?)";
            String query2 = "SELECT sanatciAdi From sanatcilar WHERE sanatciID = ?";
            PreparedStatement pst = con.prepareStatement(query2);
            pst.setInt(1, sanatciID);
            ResultSet rs1 = pst.executeQuery();
            if(rs1.next() == false){
                sanatciVarMi=false;
            }
            sanatciAdi = rs1.getString("sanatciAdi");
            String query3 = "SELECT albumAdi From albumOlustur WHERE albumID = ?";
            PreparedStatement pst3 = con.prepareStatement(query3);
            pst3.setInt(1, albumID);
            ResultSet rs3 = pst3.executeQuery();
            if(rs3.next() == false){
                albumVarMi=false;
            }
            else {
                albumVarMi=true;
                sanatciVarMi=true;
            //rs3.next();
                albumAdi = rs3.getString("albumAdi");
            
            PreparedStatement preparedStmt = con.prepareStatement(query);
            preparedStmt.setString(1, sarkiAdi);
            preparedStmt.setString(2, tarih);
            preparedStmt.setString(3, sanatciAdi);
            preparedStmt.setString(4, albumAdi);
            preparedStmt.setString(5, Tur);
            preparedStmt.setString(6, sure);
            preparedStmt.setInt(7, ahmet);
            preparedStmt.execute();
            String query5 = "insert into album (albumID, albumAdi, sanatciAdi, sarkiAdi, tarih)"
                    + " values (?,?,?,?,?)";
             PreparedStatement preparedStmt5 = con.prepareStatement(query5);
            preparedStmt5.setInt(1, albumID);
            preparedStmt5.setString(2, albumAdi);
            preparedStmt5.setString(3, sanatciAdi);
            preparedStmt5.setString(4, sarkiAdi);
            preparedStmt5.setString(5, tarih);
            preparedStmt5.execute();
            }
            con.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }    
    //sanatci ekleme
    public Mysql(int ayir,String sanatciAdi, String ulkesi) {
        try {
            Connection();
            String query = " insert into sanatcilar (sanatciAdi, ulkesi)"
                    + " values (?, ?)";
            PreparedStatement preparedStmt = con.prepareStatement(query);
            preparedStmt.setString(1, sanatciAdi);
            preparedStmt.setString(2, ulkesi);
            preparedStmt.execute();
            con.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }
    //album ekleme
    public Mysql(String albumAdi, String albumTarih, int ayir) {
        try {
            Connection();
            String query = " insert into albumOlustur (albumAdi, tarih)"
                    + " values (?, ?)";
            PreparedStatement preparedStmt = con.prepareStatement(query);
            preparedStmt.setString(1, albumAdi);
            preparedStmt.setString(2, albumTarih);
            preparedStmt.execute();
            con.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }
    //Kayit icin kullanici adi alinmis mi bakalim:
    public Mysql(String kKullaniciAdi) {
        try {
            Connection();
            String query = "SELECT kullaniciAdi From kullanicilar WHERE kullaniciAdi = ?";
            PreparedStatement pst = con.prepareStatement(query);
            pst.setString(1, kKullaniciAdi);
            ResultSet rs1 = pst.executeQuery();
            if (rs1.next() == false) {
                alinmis = false;
            } else {
                alinmis = true;
            }
            con.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    //kayit ol
    public Mysql(String kKullaniciAdi, String kSifre, boolean kAdmin, boolean kPremium,String mail) {
        this.kKullaniciAdi = kKullaniciAdi;
        this.kSifre = kSifre;
        this.kAdmin = kAdmin;
        this.kPremium = kPremium;
        try {
            Connection();
            String query = " insert into kullanicilar (kullaniciAdi, sifre, mail, premium, odendi, admin)"
                    + " values (?, ?, ?, ?, ?,?)";
            PreparedStatement preparedStmt = con.prepareStatement(query);
            preparedStmt.setString(1, kKullaniciAdi);
            preparedStmt.setString(2, kSifre);
            preparedStmt.setString(3, mail);
            preparedStmt.setBoolean(4, kPremium);
            preparedStmt.setBoolean(5, kOdendi);
            preparedStmt.setBoolean(6, kAdmin);
            preparedStmt.execute();
            playlistOlustur();
            con.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }

    //kullanici girisi
    public Mysql(String gKullaniciAdi, String gSifre) {
        try {
            Connection();
            this.gKullaniciAdi = gKullaniciAdi;
            this.gSifre = gSifre;
            String query = "SELECT kullaniciAdi From kullanicilar WHERE kullaniciAdi = ? AND sifre = ?";
            PreparedStatement pst = con.prepareStatement(query);
            pst.setString(1, gKullaniciAdi);
            pst.setString(2, gSifre);
            ResultSet rs1 = pst.executeQuery();
            if (rs1.next() == false) {
                this.kayitVarMi = 1;
            } else {
                String query2 = "SELECT * From kullanicilar WHERE kullaniciAdi = ? AND admin = ?";
                PreparedStatement pst2 = con.prepareStatement(query2);
                pst2.setString(1, gKullaniciAdi);
                pst2.setBoolean(2, true);
                ResultSet rs2 = pst2.executeQuery();
                if (rs2.next() == false) {
                    this.kayitVarMi = 3;
                } else {
                    this.kayitVarMi = 0;
                }
            }
            con.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        }
        //admin girisi
        public Mysql(boolean ayirici,String agKullaniciAdi, String agSifre) {
        try {
            Connection();
            this.agKullaniciAdi = agKullaniciAdi;
            this.agSifre = agSifre;
            String query = "SELECT kullaniciAdi From kullanicilar WHERE kullaniciAdi = ? AND sifre = ?";
            PreparedStatement pst = con.prepareStatement(query);
            pst.setString(1, agKullaniciAdi);
            pst.setString(2, agSifre);
            ResultSet rs1 = pst.executeQuery();
            if (rs1.next() == false) {
                this.akayitVarMi = 0;
            } else {
                String query2 = "SELECT * From kullanicilar WHERE kullaniciAdi = ? AND admin = ?";
                PreparedStatement pst2 = con.prepareStatement(query2);
                pst2.setString(1, agKullaniciAdi);
                pst2.setBoolean(2, true);
                ResultSet rs2 = pst2.executeQuery();
                if (rs2.next() == false) {
                    this.akayitVarMi = 1;
                } else {
                    this.akayitVarMi = 3;
                }
            }
            con.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }
    
    public void playlistOlustur() {
        try{
        Connection();
            String query5 = "CREATE TABLE " + this.kKullaniciAdi + "pop (sarkiID int)";
            String query6 = "CREATE TABLE " + this.kKullaniciAdi + "jazz (sarkiID int)";
            String query7 = "CREATE TABLE " + this.kKullaniciAdi + "klasik (sarkiID int)";
            String query8 = "CREATE TABLE " + this.kKullaniciAdi + "takipEdilenler (ID int, kullaniciAdi varchar(30))";
            // create the mysql insert preparedstatement
            PreparedStatement preparedStmt5 = con.prepareStatement(query5);
            preparedStmt5.execute();
            preparedStmt5 = con.prepareStatement(query6);
            preparedStmt5.execute();
            preparedStmt5 = con.prepareStatement(query7);
            preparedStmt5.execute();
            preparedStmt5 = con.prepareStatement(query8);
            preparedStmt5.execute();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
    public void Connection() {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            this.con = (Connection) DriverManager.getConnection("jdbc:mysql://localhost:3306/spotify", "root", "password");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
    
}

