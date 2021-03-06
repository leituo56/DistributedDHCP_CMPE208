BEGIN TRANSACTION;
CREATE TABLE "tbl_nodes" (
	`node_name`	VARCHAR(32),
	`server_ip`	INTEGER,
	`state`	INTEGER,
	`heartbeat`	INTEGER
);
INSERT INTO `tbl_nodes` VALUES('dhcpMac',2886795521,1,130);
INSERT INTO `tbl_nodes` VALUES('dhcpWin',2886795522,0,120);
CREATE TABLE "tbl_lease" (
	`lease_ip`	INTEGER,
	`hw_addr`	VARCHAR(24),
	`state`	INTEGER,
	`timeout`	INTEGER,
	`creator`	INTEGER,
	`owner`	INTEGER
);
INSERT INTO `tbl_lease` VALUES(2886795540,'84:38:35:51:e2:7e',1,500,1,2886795521);
INSERT INTO `tbl_lease` VALUES(2886795541,'32:00:1e:14:20:00',2,1000,2,2886795522);
INSERT INTO `tbl_lease` VALUES(2886795542,'b6:c5:68:5b:09:0c',5,51830498,3,2886795521);
INSERT INTO `tbl_lease` VALUES(2886795543,'06:38:35:51:e2:7e',0,300,4,2886795522);
CREATE TABLE "tbl_fixedip" (
	`hw_addr`	VARCHAR(24),
	`fixed_ip`	INTEGER,
	PRIMARY KEY(hw_addr)
);
INSERT INTO `tbl_fixedip` VALUES('32:00:1e:14:20:00',2886795530);
INSERT INTO `tbl_fixedip` VALUES('84:38:35:51:e2:7e',2886795531);
INSERT INTO `tbl_fixedip` VALUES('06:38:35:51:e2:7e',2886795532);
INSERT INTO `tbl_fixedip` VALUES('b6:c5:68:5b:09:0c',2886795533);
CREATE TABLE "tbl_cfg" (
	`key`	VARCHAR(32),
	`val`	INTEGER
);
INSERT INTO `tbl_cfg` VALUES('range_start',2886795530);
INSERT INTO `tbl_cfg` VALUES('range_end',2886795570);
INSERT INTO `tbl_cfg` VALUES('subnetmask',4294967040);
INSERT INTO `tbl_cfg` VALUES('router',2886795521);
INSERT INTO `tbl_cfg` VALUES('lease_time',3600);
;
COMMIT;
