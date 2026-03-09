import jwtService from '../services/jwt.js';

export async function authenticateJWT(request, reply) {
	const authHeader = request.headers.authorization;

	if (!authHeader?.startsWith('Bearer ')) {
		return reply.status(401).send({
			success: false,
			error: 'auth.authenticationRequired'
		});
	}

	const token = authHeader.substring(7).trim();
	const decoded = await jwtService.verifyToken(token);

	if (!decoded) {
		return reply.status(401).send({
			success: false,
			error: 'auth.invalidToken'
		});
	}

	request.user = decoded;
}
