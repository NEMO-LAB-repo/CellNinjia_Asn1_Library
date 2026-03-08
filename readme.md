# CellNinja ASN.1 Decoder Library

A shared C library for decoding Qualcomm modem diagnostic log packets (LTE and NR5G) using ASN.1-defined message structures. 

## Building

### Prerequisites

- GCC with shared library support
- [asn1c velichkov_s1ap_plus_option_group branch](https://github.com/brchiu/asn1c/tree/velichkov_s1ap_plus_option_group)

### Compile the library

```sh
cd asn1_group

# Step 1: Generate C source files from all ASN.1 schemas
./ASN1_compile.sh

# Step 2: Remove the standalone entry point (not needed for shared library)
rm converter-example.c

# Step 3: Build the shared library
gcc -fPIC -shared -o libcellninja_asn1.so *.c -I.
```

The output is `libcellninja_asn1.so`, which can be loaded dynamically by the CellNinja_desktop.

---

## Contributing a New Message Type or New Message Version

To add decoding support for a new log message, follow these steps:

### 1. Add the ASN.1 schema

Place your `.asn1` file in `asn1_group/`. Name it after the message type, e.g.:

```
asn1_group/NR5G_MAC_MyNewMessage.asn1
```

### 2. Register the schema in the compile script

Add an `asn1c` invocation to [asn1_group/ASN1_compile.sh](asn1_group/ASN1_compile.sh):

```sh
asn1c -S /usr/local/share/asn1c \
  -fcompound-names -fskeletons-copy -findirect-choice \
  -fincludes-quoted -fno-include-deps -pdu=auto \
  NR5G_MAC_MyNewMessage.asn1
```

### 3. Implement the decoder

Create `asn1_group/BXXX_cb_dcall.c` with your decode function.  
Look at an existing implementation such as [asn1_group/B885_cb_dcall.c](asn1_group/B885_cb_dcall.c) as a reference.

### 4. Register the decoder in host.h and host.c

In [asn1_group/host.h](asn1_group/host.h), declare your function.  
In [asn1_group/host.c](asn1_group/host.c), add a dispatch entry that maps the log code `0xBXXX` and version to your decode function.


---

## Supported Message Types

### LTE

| # | Message Name | Log Code | Version |
|---|---|---|---|
| 1 | LTE RLC DL AM Control PDU | 0xB083 | 48 |
| 2 | LTE PDCP DL Data PDU | 0xB0A1 | 53 |
| 3 | LTE PDCP UL Delay Statistics | 0xB0B6 | 56 |
| 4 | LTE RRC Supported CA Combos | 0xB0CD | 41 |
| 5 | LTE LL1 Serving Cell Measurement Results | 0xB116 | 21 |
| 6 | LTE LL1 PCFICH Decoding Results | 0xB12A | 161 |
| 7 | LTE LL1 RACH TX Report | 0xB144 | 161 |
| 8 | LTE ML1 Random Access Request MSG1 Report | 0xB167 | 40 |
| 9 | LTE ML1 Random Access Response MSG2 Report | 0xB168 | 24 |
| 10 | LTE UE Identification Message MSG3 Report | 0xB169 | 40 |
| 11 | LTE Contention Resolution Message MSG4 Report | 0xB16A | 1 |
| 12 | LTE ML1 DCI Information Report | 0xB16C | 49 |
| 13 | LTE ML1 GM TX Report | 0xB16D | 49 |
| 14 | LTE ML1 PDSCH Stat Indication | 0xB173 | 48 |
| 15 | LTE ML1 S Criteria Check Procedure | 0xB17A | 1 |
| 16 | LTE ML1 Idle Measurement Request | 0xB17D | 1 |
| 17 | LTE ML1 Serving Cell Measurements And Evaluation | 0xB17F | 5 |
| 18 | LTE ML1 Intra Frequency Cell Reselection Payload | 0xB181 | 1 |
| 19 | LTE ML1 CA Metrics Log Packet | 0xB184 | 50 |
| 20 | LTE ML1 AdvRx IC Cell List | 0xB18F | 54 |
| 21 | LTE ML1 Cell Measurement Results | 0xB196 | 41 |
| 22 | LTE ML1 Serving Cell Information | 0xB197 | 2 |
| 23 | LTE ML1 Common DC Offset | 0xB1B2 | 49 |
| 24 | LTE RRC OTA Packet | 0xB0C0 | 16.1.0 |

### NR5G

| # | Message Name | Log Code | Version |
|---|---|---|---|
| 1 | NR5G NAS SM5G Plain OTA Outgoing Msg | 0xB800 | 1 |
| 2 | NR5G NAS Plain Message Container | 0xB814 | 1 |
| 3 | NR5G NAS MM5G NSSAI Info | 0xB815 | 1 |
| 4 | NR5G NAS MM5G State | 0xB80C | 1 |
| 5 | NR5G RRC OTA Packet | 0xB821 | 15.10.0 / 16.6.0 / 17.2.0 |
| 6 | NR5G RRC MIB Info | 0xB822 | 1 |
| 7 | NR5G RRC Serving Cell Info | 0xB823 | 4 |
| 8 | NR5G RRC Configuration Info | 0xB825 | 8 |
| 9 | NR5G RRC Supported CA Combos | 0xB826 | 7 |
| 10 | NR5G PDCP DL Data Pdu | 0xB840 | 6 |
| 11 | NR5G PDCP DL Rbs Stats | 0xB842 | 5 |
| 12 | NR5G RLC DL Stats | 0xB84D | 196608 |
| 13 | NR5G RLC DL Status PDU | 0xB84E | 1 |
| 14 | NR5G L2 DL Config | 0xB84B | 5 |
| 15 | NR5G L2 DL DATA PDU | 0xB857 | 6 |
| 16 | NR5G PDCP UL Stats | 0xB860 | 9 |
| 17 | NR5G PDCP UL Control Pdu | 0xB861 | 196609 |
| 18 | NR5G RLC UL Stats | 0xB868 | 4 |
| 19 | NR5G RLC UL Status PDU | 0xB869 | 196609 |
| 20 | NR5G L2 UL Data PDU | 0xB870 | 196611 |
| 21 | NR5G L2 UL Config | 0xB871 | 5 |
| 22 | NR5G L2 UL TB | 0xB872 | 4 / 196616 |
| 23 | NR5G L2 UL BSR | 0xB873 | 196611 |
| 24 | NR5G MAC UL TB Stats | 0xB881 | 196609 |
| 25 | NR5G MAC UL Physical Channel Schedule Report | 0xB883 | 196623 |
| 26 | NR5G MAC DCI Info | 0xB885 | 131077 / 196617 |
| 27 | NR5G MAC DL TB Report | 0xB886 | 3 |
| 28 | NR5G MAC PDSCH Status | 0xB887 | 5 / 196611 |
| 29 | NR5G MAC PDSCH Stats | 0xB888 | 196608 |
| 30 | NR5G MAC RACH Trigger | 0xB889 | 196615 |
| 31 | NR5G MAC CDRX Events Info | 0xB890 | 131073 |
| 32 | NR5G MAC UCI Information | 0xB89B | 2 / 196608 |
| 33 | NR5G MAC Flow Control | 0xB89C | 131073 |
| 34 | NR5G MAC CSF Report | 0xB8A7 | 131073 / 196613 |
| 35 | NR5G LL1 FW Serving FTL | 0xB8DD | 7 |
| 36 | NR5G LL1 FW RX Control AGC | 0xB8C9 | 131072 |
| 37 | NR5G ML1 Searcher Measurement Database Update Ext | 0xB97F | 131081 |
| 38 | NR5G ML1 Searcher Conn Eval | 0xB96F | 131075 |
| 39 | NR5G ML1 Antenna Switch Diversity | 0xB98F | 131074 |
| 40 | NR5G ML1 Search HO Acq Confirm | 0xB9BF | 131079 |

---
