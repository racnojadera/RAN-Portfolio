dictionary_equivalent = {
    "a" : "e",
    "b" : "p",
    "c" : "s",
    "d" : "t",
    "e" : "i",
    "f" : "w",
    "g" : "k",
    "h" : "n",
    "i" : "u",
    "j" : "v",
    "k" : "g",
    "l" : "c",
    "m" : "l",
    "n" : "r",
    "o" : "y",
    "p" : "b",
    "q" : "x",
    "r" : "h",
    "s" : "m",
    "t" : "d",
    "u" : "o",
    "v" : "f",
    "w" : "z",
    "x" : "q",
    "y" : "a",
    "z" : "j"
    }

def dumb_decryption(s):
    output = ''
    for i in s.lower():
        if i in dictionary_equivalent:
            output += dictionary_equivalent[i]
        else:
            output += i
        
    return output

cipherparagraph1 = 'Puhic Yccekhsahd. Drec ec yh ehtejetiym puhic yldejedo. Ra fru lyh cipsed y bodruh clnebd (hud hudapuug) du dnyhcmyda drec daqd YHT damm sa fryd NBK drec fyc bubimynewat fedr femm kad y dfahdo buehd puhic eh dra yccekhsahdc. Kuut milg'
cipherparagraph2 = 'Cusa yttedeuhym daqd du ramb talutehk. "Dra xielg pnufh vuq zisbc ujan dra mywo tuk" ec yh Ahkmecr-myhkiyka byhknys—y cahdahla dryd luhdyehc ymm uv dra maddanc uv dra ymbrypad. Ed ec lussuhmo icat vun duilr-dobehk bnyldela, dacdehk dobafnedanc yht lusbidan gaopuyntc, tecbmyoehk aqysbmac uv vuhdc, yht udran ybbmelydeuhc ehjumjehk daqd frana dra ica uv ymm maddanc eh dra ymbrypad ec tacenat. Ufehk du edc pnajedo yht luranahla, ed ryc palusa fetamo ghufh.'

print(dumb_decryption(cipherparagraph1))
print()
print(dumb_decryption(cipherparagraph2))

#The role-playing game that popularized using ciphers as a form of puzzle/easter eggs is Final Fantasy X-2. This was particularly used in acessing Besaid Cave in which the players had to find a 4-digit code to input in the cave's entrance.