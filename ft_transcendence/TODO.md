# TODO

**Organization:**
- **Track contributors**: Add your username when creating tasks (e.g., `lcuevas- / todo`), and note who solved them when completed (e.g., `lcuevas- / pausanch`)
- **High and Medium Priority**: Active todo lists that can be checked off or expanded as needed.
- **Low Priority / Bug Reports**: Numbered list for tracking issues. When resolved, move entries to the "Solved Bug Reports" section below.


## High Priority
- [ ] General testing of endpoints. Codes an errors messages seem fine, frontend should handle that gracefully.
Basically when we return an error on a api request, instead of do a condole.error we handle it "gracefully". 21, 23, 26, 27 
Also Post, Put, Delete etc... should be protected from unexpeected imput (lcuevas- / todo)
- [x] Everything is runing dinamically, game keeps running in the background. Maybe load and refresh pages less dinamically? Bug report 15 (lcuevas- / todo)

### Database Schema
- [x] Database schema for README (lcuevas- / lcuevas-)
- [x] Database schema must be updated in the final version. Bug report 7(lcuevas- / lcuevas-)

### Docker Configuration
- [x] Prepare final production version without bind-mounts (lcuevas- / lcuevas-)
- [x] Nginx must generate the certificates at runtime (lcuevas- / lcuevas)

### Git comments
- [x] Investigate changing git comments history. We will not do it at the moment (lcuevas- / todo)

### Authentications
- [x] Oauth need api keys to be configured? (lcuevas- / csubires)

## Medium Priority
- [ ] Check friends list UI (show friends, online status, send requests) (lcuevas- / todo)
- [ ] Check tournament UI and matchmaking logic (lcuevas- / todo)
- [x] Profile page: show user stats & match history. Bug report 11 (lcuevas- / todo)
- [x] Add Leaderboards: Bug report 12 (lcuevas- / lcuevas-)
- [x]TicTacToe integration with gameService. Bug report 16 (lcuevas- / pausanch)
- [ ] Database service is in realuty UserManagement service, should we change anything? (lcuevas- / todo)


### Documentation
- [x] Update README.md (lcuevas- / lcuevas-)
- [x] Privacy Policy and Terms of services, accesible and tick in the registration (lcuevas- / lcuevas-)


## Low Priority / Bug reports
- [x] **001**: Update button in profile page overwrites the image. We can recicle to change the mail, maybe (lcuevas- / lcuevas-)
- [ ] **002**: Check erase od information and account in GDPR (lcuevas- / todo)
- [x] **003**: Error mensajes in the log due to console.errors in the frontend pages.ts files. some can just be reordenated. Example in loadPLayers in players.ts. We should Check every console.error and console.log (lcuevas- / lcuevas-)
- [x] **004**: Similarly to 003, there are network errors when the api "fails" even in a expcted way. (lcuevas- / lcuevas-)
- [x] **005**: Navbar interfered with responsiveness. Improved resnposive changes in general. (lcuevas- / lcuevas-)
- [x] **006**: Navbar is not translated. Some buttons like "Dashboard" and titles  like "Players" in front page also (lcuevas- / pausanch)
- [x] **007**: Update database scheme in README and image to the last version with tournament and sessions? (lcuevas- / lcuevas-)
- [x] **008**: Handling fetch error when failing to log a player as second player in a match (lcuevas- / lcuevas-)
- [x] **009**: You cna play against yourself if logged in (lcuevas- / lcuevas-)
- [x] **010**: Check friends process and online status (lcuevas- / todo)
- [x] **011**: Add button for extra information in profile page, like the cards we render and such (lcuevas- / lcuevas-)
- [x] **012**: Make the leaderboard. (lcuevas- / lcuevas-)
- [x] **013**: Oauth 2 Deactivated, reactivate with API key?. (lcuevas- / csubires)
- [x] **014**: IA movement overshoots and never stop mooving. (lcuevas- / pausanch)
- [X] **015**: Games keep runing in backgorund if we change pages. (lcuevas- / pausanch)
- [X] **016**: Tic-Tac-Toe does not track matches. (lcuevas- / pausanch)
- [X] **017**: Check subject compliance for Games Customization module. (lcuevas- / pausanch)
- [x] **018**: Promehteus and grapahan are deactivated. (lcuevas- / csubires)
- [x] **019**: Clean references to old users module, grapahan and prometheus (lcuevas- / everyone)
- [ ] **020**: Check GDPR module for new requisites, like requesting data via mail (lcuevas- / todo)
- [x] **021**: Logout button behaves weirdly. Check browser console nad network (lcuevas- / todo)
- [X] **022**: Privacy Policy and Terms of Service are not translated. Don't know if it needs it (lcuevas- / pausanch)
- [x] **023**: Log out button make a strange network error. Also console shows 400 bad request. SHould look into that (lcuevas- / lceuvas-)
- [X] **024**: Match History cut on the bottom in profile (pausanch / pausanch)
- [X] **025**: Match History don't show type of game (pausanch / pausanch)
- [x] **026**: Dashboard without loging shows a 502. May be for deprecated fetch, also protect better the endpoint(lcuevas- / lceuvas-)
- [x] **027**: Like we said, some POST are not protected.  cahnge-lenguaje with nothing inside makes a error 500 (lcuevas- / todo)
- [x] **028**: Nickname update is not parsed and can load a text as long as you want. Let's cut it to 10 or something (lcuevas- / lcuevas-)
- [x] **029**: After Erasing image there is some kind of cors error. Also check if we just make it null, maybe players is trying to load the image and when failing is doing osmething and showing error. Maybe is about the github image (lcuevas- / csubires)
- [x] **030**: PLayers page return too much information?, id and name?. At least ID should not be return. (lcuevas- / lcuevas-)
- [x] **031**: Check and edit or take out search button in frineds. At least ID should not be return. (lcuevas- / lcuevas-)
- [x] **032**: Aded security audit file wiht some problematic endpoints. (lcuevas- / lcuevas-)
- [x] **033**: It seems we make a lot of endpoints generate generic errors, 400 or 500, we have to change that to specific ones and handle it in the forntend (lcuevas- / lcuevas-)
- [ ] **034**: Better check the responsivnes of the profile page, seem to have some limits (lcuevas- / todo)
- [x] **035**: After restarting gateway the IP changes. Added a retry part on the nginx.conf (lcuevas- / lcuevas-)
- [x] **036**: Database behaved weirdly with caches and disasters and make error 500 after erasing it. AUtomated recoveries. (lcuevas- / lcuevas-)
- [x] **037**: 2fa recovery codes can't be used. (lcuevas- / lcuevas-)
- [x] **038**: Check mail validation for trash and wier characters. (lcuevas- / csubires)
- [x] **039**: Erase avatar with ouauth does not work. MOst probably it does not erase the users table text. (lcuevas- / csubires)
- [ ] **040**: A couple of alerts, like when erasing avatar. Check validity of that (lcuevas- / TODO)
- [x] **041**: Clean Grapahana and Prometheus and test api from dashboard (lcuevas- / lcuevas-)
- [x] **042**: Tournament with tictactoe do not report and load properly, it checks as pong (joestrad- / joestrad)
- [x] **043**: When adding multiple registered players old fields get erased (lcuevas- / joestrad)
- [x] **044**: Test page to be eliminated (csubires / joestrad)


# Solved Bug reports

- [x] **003**: Error mensajes in the log due to console.errors in the frontend pages.ts files. some can just be reordenated. Example in loadPLayers in players.ts. We should Check every console.error and console.log (lcuevas- / lcuevas-)
- [x] **004**: Similarly to 003, there are network errors when the api "fails" even in a expcted way. This is due to the browser DevTools, we CAN NOT silence that, our backend is correct. The frontend handle it gracefully, but hte devtools will launch that everytime since it is monitoring the requests. (lcuevas- / lcuevas-)
- [x] **005**: Navbar interfered with responsiveness. Improved resnposive changes in general. (lcuevas- / lcuevas-)
- [x] **008**: Handling fetch error when failing to log a player as second player in a match (lcuevas- / lcuevas-)
- [x] **009**: You cna play against yourself if logged in (lcuevas- / lcuevas-)
- [X] **015**: Games keep runing in backgorund if we change pages. General strucutre mantained, used listeners to stop game gracefully (lcuevas- / pausanch)
- [x] **001**: Update button in profile page overwrites the image. We can recicle to change the mail, maybe. Recicled the button for mail updating. Mail is validated and Also imprived translation and (lcuevas- / lcuevas-)
- [x] **011**: Ad button for exra information in profile page, like the cards we render and such (lcuevas- / lcuevas-)
- [X] **016**: Tic-Tac-Toe does not track matches. Recicle function from pong (lcuevas- / pausanch)
- [X] **024**: Match History cut on the bottom in profile. The container was cropped so that it does not occupy the footer and does not hide behind it. (pausanch / pausanch)
- [X] **025**: Match History don't show type of game. I added a new variable so that the game appears in the history. (pausanch / pausanch)
- [x] **030**: PLayers page return too much information?, id and name?. At least ID should not be return. Changed to use username as public identifier instead of exposing internal database IDs. (lcuevas- / lcuevas-)
- [x] **032**: Aded security audit file wiht some problematic endpoints. Fixed 1 and 2, 3 to 6 are from the tournament  (lcuevas- / lcuevas-)
- [x] **028**: Nickname update is not parsed and can load a text as long as you want. Parsed on frotnend and backend (lcuevas- / lcuevas-)
- [x] **006**: Navbar is not translated. Some buttons like "Dashboard" and titles  like "Players" in front page also (lcuevas- / pausanch)
- [x] **021**: Logout button behaves weirdly. Check browser console nad network. The endpoint was deprecated, enrouted to a valid exisiting one and parsed some errors. Also it needed a body to be accepted
Also aded empty body to /api/2fa/backup-codes/generate (lcuevas- / lcuevas-)
- [x] **023**: Log out button make a strange network error. Also console shows 400 bad request. SHould look into that same thing as 21, that fixed it(lcuevas- / lceuvas-)
- [x] **035**: After restarting gateway the IP changes. Added a retry part on the nginx.conf (lcuevas- / lcuevas-)
Also aded empty body to /api/2fa/backup-codes/generate (lcuevas- / lcuevas-)
- [x] **036**: Database behaved weirdly with caches and disasters and make error 500 after erasing it. AUtomated recoveries. (lcuevas- / lcuevas-)
- [x] **033**: It seems we make a lot of endpoints generate generic errors, 400 or 500, we have to change that to specific ones and handle it in the forntend. Made a bunch of generic messages in the api.ts, no the endpoints always answer personalized errors, never generic 400 or 500. Someone should check if I have forgot about any (lcuevas- / lcuevas-)
- [x] **029**: After Erasing image there is some kind of cors error. Also check if we just make it null, maybe players is trying to load the image and when failing is doing osmething and showing error. Maybe is about the github image. Fixed with the github cors fiasco too(lcuevas- / csubires)
- [x] **027**: Like we said, some POST are not protected.  cahnge-lenguaje with nothing inside makes a error 500. htey where protected, we just ahd to fix the codes. Tournament endpoints should be checked anyway, like the audit says (lcuevas- / joestrad)
- [x] **018**: Promehteus and grapahan are deactivated. THey will be out ot the final product for the time being(lcuevas- / csubires)
- [x] **014**: IA movement overshoots and never stop mooving. It is better now with higer difficulties. Even tho is true that it is always mooving, but that makes it able to loose (lcuevas- / pausanch)
- [x] **013**: Oauth 2 Deactivated, reactivate with API key?. Reactivated, now we need a .env with some credentials, csubires are the ones that we use at the moment (lcuevas- / csubires)
- [x] **037**: 2fa recovery codes can't be used. They needed to be regostered as a public route and logic had to be updated. Translation updated (lcuevas- / lcuevas-)
- [x] **032**: Aded security audit file wiht some problematic endpoints. Moved to deprecated_docs folder (lcuevas- / lcuevas-)
- [x] **012**: Make the leaderboard. Added to the player pages with translations and new enpoints in players.js and tournaments.js (lcuevas- / lcuevas-)
- [x] **007**: Update database scheme in README and image to the last version with tournament and sessions. Schema is complete with all tables documented. Image updated too (lcuevas- / lcuevas-)
- [x] **010**: Check friends process and online status. Takes time but saeems to work (lcuevas- / todo)
- [x] **019**: Clean references to old users module, grapahan and prometheus (lcuevas- / everyone)
- [x] **026**: Dashboard without loging shows a 502. May be for deprecated fetch, also protect better the endpoint. Just erased all calls and references to users (lcuevas- / lceuvas-)
- [x] **039**: Erase avatar with ouauth does not work. MOst probably it does not erase the users table text. Just needed to reorder the endpoint to NULL the users table avatar even if there is no file to erase in the image database (lcuevas- / csubires)
- [x] **038**: Check mail validation for trash and wier characters. Hardened validation rules (lcuevas- / csubires)
- [x] **042**: Tournament with tictactoe do not report and load properly, it checks as pong. Added new variable in the tournament table, now is carreid from the frontend and upstream (joestrad- / joestrad)
- [x] **043**: When adding multiple registered players old fields get erased. Better modals and variables now (lcuevas- / joestrad)
- [x] **044**: Test page to be eliminated. Done, with all references (csubires / joestrad)
- [x] **041**: Clean Grapahana and Prometheus and test api from dashboard. Cleaned dashboard (lcuevas- / lcuevas-)