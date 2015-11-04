DROP TABLE match_profile CASCADE;
DROP TABLE match CASCADE ;
DROP TABLE profile CASCADE;
DROP TABLE room CASCADE;
DROP TABLE request CASCADE;

CREATE TABLE match(
id SERIAL,

PRIMARY KEY(id)
);

CREATE TABLE profile(
id SERIAL,
name VARCHAR(200),

PRIMARY KEY(id)
);

CREATE TABLE match_profile(
id SERIAL,
id_match INTEGER,
id_profile INTEGER,
team INTEGER,

PRIMARY KEY(id),
FOREIGN KEY(id_match) references match(id),
FOREIGN KEY(id_profile) references profile(id)
);

CREATE TABLE room(
id SERIAL,
id_match INTEGER,
available VARCHAR(1) DEFAULT 'N',
server_address VARCHAR(300) DEFAULT '',

PRIMARY KEY(id),
FOREIGN KEY(id_match) references match(id)
);

CREATE TABLE request(
id SERIAL,
state VARCHAR(1),
id_profile INTEGER,
id_room INTEGER,

PRIMARY KEY(id),
FOREIGN KEY(id_profile) REFERENCES profile(id),
FOREIGN KEY(id_room) REFERENCES room(id)
);

INSERT INTO profile(name) values('Rodrigo');
