--- if_wg.c.orig	2021-04-29 01:49:46 UTC
+++ if_wg.c
@@ -92,6 +92,7 @@ __FBSDID("$FreeBSD$");
 #define UNDERLOAD_TIMEOUT	1
 
 #define DPRINTF(sc, ...) if (sc->sc_ifp->if_flags & IFF_DEBUG) if_printf(sc->sc_ifp, ##__VA_ARGS__)
+#define PRINTF(sc, ...) if (sc->sc_ifp->if_flags) if_printf(sc->sc_ifp, ##__VA_ARGS__)
 
 /* First byte indicating packet type on the wire */
 #define WG_PKT_INITIATION htole32(1)
@@ -1353,6 +1354,9 @@ wg_handshake(struct wg_softc *sc, struct wg_packet *pk
 		peer = noise_remote_arg(remote);
 
 		DPRINTF(sc, "Receiving handshake initiation from peer %" PRIu64 "\n", peer->p_id);
+                char peer_ip[INET6_ADDRSTRLEN];
+                inet_ntop(pkt->p_endpoint.e_remote.r_sin.sin_family , &pkt->p_endpoint.e_remote.r_sin.sin_addr , peer_ip, sizeof(peer_ip));
+		PRINTF(sc, "Receiving handshake initiation from peer %" PRIu64 " %s \n", peer->p_id , peer_ip);
 
 		wg_peer_set_endpoint(peer, &pkt->p_endpoint);
 		wg_send_response(peer);
