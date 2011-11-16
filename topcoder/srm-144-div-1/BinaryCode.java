public class BinaryCode {
    public String[] decode(String message) {
        return new String[] {
            decodeAssuming(0, message), decodeAssuming(1, message) };
    }

    private String decodeAssuming(int first, String msg) {
        int len = msg.length();
        int[] val = new int[len + 2];
        val[1] = first;
        for (int i = 1; i <= len; i++) {
            int enc = msg.charAt(i-1) - '0';
            int dec = enc - (val[i] + val[i-1]);
            if (dec != 0 && dec != 1) return "NONE";
            val[i+1] = dec;
        }
        if (val[len + 1] != 0) return "NONE";
        StringBuilder sb = new StringBuilder();
        for (int i = 1; i <= len; i++)
            sb.append(val[i]);
        return sb.toString();
    }
}
