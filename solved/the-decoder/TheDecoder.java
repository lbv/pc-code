import java.io.*;
import java.util.*;

public class TheDecoder {
    public static void main(String[] args) throws IOException {
        InputStream $r = new DataInputStream(System.in);
        OutputStream $w = new DataOutputStream(System.out);

        while (true) {
            int c = $r.read();
            if (c < 0) break;

            if (c != 10 && c != 13)
                c -= 7;

            $w.write(c);
        }

        $w.close();
    }
}
